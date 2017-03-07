//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include "Server.h"
#include "pkt_m.h"
#include "PyxisDefs.h"

namespace pyxis {

Define_Module(Server);

Server::Server()
{
    slotEvent = new cMessage("Slot");
    bcs_pkt = new BasePkt("BCS");
    newPkt  = new cMessage("PBData");
    queue = new cPacketQueue("Buffer");
}

Server::~Server()
{
    cancelAndDelete(slotEvent);
    cancelAndDelete(newPkt);
    delete bcs_pkt;

    while (!queue->isEmpty())
    {
        cPacket* p = queue->pop();
        delete p;
    }

    delete queue;
}

void Server::initialize()
{
    server = getModuleByPath("server");
    if (!server)
        throw cRuntimeError("server not found");

    collisionsBase  = registerSignal("collisionsAtBase");
    allocatedBps    = registerSignal("allocatedBps");
    requestedBps    = registerSignal("requestedBps");
    efficiency      = registerSignal("efficiency");
    business        = registerSignal("business");

    txRx            = par("txRx");
    slotTime        = par("slotTime");
    maxCycleSlots   = par("cycleSlots");
    numHosts        = par("numHosts");
    ARSmin          = par("ARSmin");
    ARSmax          = par("ARSmax");
    slotBytes       = par("slotBytes");
    iaTime          = &par("iaTime");
    dataLen         = par("dataLen");
    backOff         = par("backOff");
    maxPGBK         = par("maxPGBK");
    BCSlot          = par("BCSlot");
    firstSlotBytes  = par("firstSlotBytes");

    if (backOff == (int)BACKOFF_HARMONIC)   // for HarmonicBackOff find the smallest size window
        ARSmax = ARSmin;

    ARSlot = ARSmin;

    for (int i = 0; i < numHosts; i++)
        gate("in", i)->setDeliverOnReceptionStart(true);

    initEvalSlots(ARSlot);
    cycleSlots = ARSlot + BCSlot;
    SSlot = 0;  // no data at the start
    cycleCnt = 0;

    jl = new JoinLeave(bcs_pkt, numHosts);
    sc = new Scheduler(numHosts, maxCycleSlots, ARSlot + BCSlot, maxPGBK);
    df = new Defragmenter(slotBytes, firstSlotBytes);

    pid = PID_PB;

    myMAC = this->getMAC();
    srand(getId());

    logicSlotCnt = 0;
    tmpSlotCnt = -1;        // used to differentiate between current LTS
    scheduleAt(getNextSlotTime(), slotEvent);
    scheduleAt(getNextPktTime(), newPkt);       // event to add new packet into queue
}

void Server::handleMessage(cMessage *msg)
{
    // time slot tick event
    if (msg->isSelfMessage())
    {
        if (newPkt == msg)  // new fifo packet
        {
            queue->insert(new cPacket("OTAP", 0, 8 * dataLen));
            scheduleAt(getNextPktTime(), newPkt);
            return;
        }

        if (0 == logicSlotCnt % cycleSlots)  // one cycle passed
        {
            logicSlotCnt = 0;
            cycleCnt++;
        }

        if (logicSlotCnt == 0) // may always be sent from ts0
        {
            tmpSlotCnt = -1;
            this->downMessage(bcs_pkt);
            jl->clearJoinInBCS(bcs_pkt);
        }

        ++logicSlotCnt;

        scheduleAt(getNextSlotTime(), msg);
        return;
    }

    receiveRemote((cPacket *)msg);
    delete msg;
}

simtime_t Server::getNextSlotTime()
{
    simtime_t t = simTime() + slotTime;
    return t;
}

simtime_t Server::getNextPktTime()
{
    return (simTime() + iaTime->doubleValue());
}

int Server::numOfTxDBits(int frames)
{
    int bytes;

    double s = maxCycleSlots * (slotTime.dbl() + txRx.dbl());

    if (frames < 1)
        bytes = 0;
    else
        bytes = firstSlotBytes + slotBytes * (frames - 1);

    return (long)(8 * bytes / s);
}

/* Base BCS packet
 * The one and only TDM advertisement
 * */
void Server::downMessage(BasePkt *pkt)
{
    int max_alc;

    pkt->setPid(pid);
    pkt->setLts(logicSlotCnt);

    // Work out the size of new ARS before advertising it
    this->updateARSlot();
    pkt->setARS(ARSlot);

    // Base requests addition
    this->PBRequest();

    // Data allocation for all network
    sc->allocate();

    // Collect stats
    emit(allocatedBps, numOfTxDBits(sc->getNumOfAllocatedFrames()));
    emit(requestedBps, numOfTxDBits(sc->getNumOfRequestedFrames()));

    if (0 < (max_alc = sc->getNumOfAllocated()))
    {
        pkt->setAlloc_pidsArraySize(max_alc);
        pkt->setAlloc_framesArraySize(max_alc);
        for (int j = 0; j < max_alc; j++)
        {
            pkt->setAlloc_pids(j, sc->getAllocatedPID(j));
            pkt->setAlloc_frames(j, sc->getAllocatedFrames(j));
            EV << "ALLOCATED > " << sc->getAllocatedFrames(j) << " frames to PID " << sc->getAllocatedPID(j) << "\n";
        }
    }

    // Allocate data slots for Base
    this->PBScheduleData();

    // Handle piggybacked part of packet
    pkt->setPgbksArraySize(numHosts);
    for (int i = 0; i < numHosts; i++)
        pkt->setPgbks(i, sc->getPGBKCnt(i));

    SSlot = sc->getNeededDataFrames();

    cycleSlots = BCSlot + ARSlot + SSlot;

    emit(efficiency, (double)(SSlot)/cycleSlots);
    emit(business, (double)(SSlot)/(maxCycleSlots - BCSlot - ARSlot));

    if (cycleSlots > maxCycleSlots)
    {
        cycleSlots = maxCycleSlots;
        SSlot = cycleSlots - BCSlot - ARSlot;
    }

    pkt->setCycleSlots(cycleSlots);

    // fill in failed slots from last cycle
    pkt->setFailedSlotsArraySize(ARSlot);
    int fcnt = 0;
    for (int i = 0; i < ARSlot; i++)
    {
        pkt->setFailedSlots(i, failedSlots[i]);
        if (failedSlots[i])
            fcnt++;
    }

    if (fcnt && hasGUI())
    {
        char buf[64];
        sprintf(buf, "Failed %d out of %d slots", fcnt, ARSlot);
        bubble(buf);
    }

    //TODO: add errors to swap ---> p->setBitError(false);

    for (int i = 0; i < numHosts; i++)
    {
        cMessage *copy = ((cMessage *)pkt)->dup();
        send(copy, "out", i);
    }

    // Initialize failed slot information for next cycle
    initEvalSlots(ARSlot);
    sc->clearRequests(maxCycleSlots, ARSlot + BCSlot);
    sc->clearAllocations();
    for (int i = 0; i < max_alc; i++)
    {
        pkt->setAlloc_pids(i, EMPTY_PID);
        pkt->setAlloc_frames(i, 0);
    }

}

void Server::PBRequest()
{
    char eve[90] = {0};
    int frames = df->queue2frames(queue->getByteLength());

    if (frames)
    {
        sc->addDataRequest(pid, frames, uniform(0.0, 1.0, 1), eve);
        EV << eve;
    }
}

void Server::PBScheduleData()
{
    cPacket* p;
    static int frame_count = 0;
    int frames, max_alc = sc->getNumOfAllocated();
    int frames_in_data = df->framesInData(dataLen);

    for (int j = 0; j < max_alc; j++)
    {
        if (pid == sc->getAllocatedPID(j))
        {
            if (0 < (frames = sc->getAllocatedFrames(j)))
            {
                EV << "ALLOCATED > " << sc->getAllocatedFrames(j) << " frames to PB (BASE)\n";

                frame_count += frames;

                if (frame_count == frames_in_data)   // received the exactly 1 packet allocation
                {
                    if (!queue->isEmpty())
                    {
                        p = queue->pop();
                        delete p;
                        EV << "Server>released exactly 1 pkt\n";
                    }

                    frame_count = 0;
                }
                else if (frame_count > frames_in_data)
                {
                    int pkts = frame_count / frames_in_data;
                    for (int i = 0; i < pkts; i++)
                    {
                        if (!queue->isEmpty())
                        {
                            p = queue->pop();
                            delete p;
                        }
                    }
                    frame_count = frame_count % frames_in_data;
                    EV << "Server>released " << pkts << " packets and left with " << frame_count << " frames\n";
                }
                else
                {
                    EV << "Server>dealt with " << frame_count << " out of " << frames_in_data << " data packet frames\n";
                }
            }
        }
    }

}


void Server::initEvalSlots(int slots)
{
    if (failedSlots != NULL)
        delete failedSlots;

    failedSlots = new bool[slots];

    for (int i = 0; i < slots; i++)
        failedSlots[i] = false;

    if (reservedSlots != NULL)
        delete reservedSlots;

    reservedSlots = new bool[slots];

    for (int i = 0; i < slots; i++)
        reservedSlots[i] = false;
}

void Server::updateARSlot()
{
    int m, r = 0, f = 0;

    for (int i = 0; i < ARSlot; i++)
    {
       if (failedSlots[i])  // slots with collisions, n_c(t)
          f++;

       if (reservedSlots[i])    // successfully reserved slots, n_s(t)
          r++;
    }

    if (backOff != (int)BACKOFF_HARMONIC)
    {
        m = 2*f + r;    // MLE estimate taken from RMAC

        if (m > ARSmax)
            m = ARSmax;

        if (m < ARSmin)
            m = ARSmin;

        ARSlot = m;
    }

    emit(collisionsBase, ((double)f)/ARSlot);
}

void Server::receiveRemote(cPacket* msg)
{
    static int txSlot = -1;

    if (tmpSlotCnt != logicSlotCnt)
    {
        tmpSlotCnt = logicSlotCnt;

        if (JOIN_PKT_TYPE == msg->getKind())
        {
            txSlot = ((JoinPkt *)msg)->getLts();
            processJoin((JoinPkt *)msg);
        }
        else if (REQ_PKT_TYPE == msg->getKind())
        {
            if (logicSlotCnt < ARSlot + BCSlot && logicSlotCnt >= BCSlot)
                reservedSlots[logicSlotCnt - BCSlot] = true;
            txSlot = ((RequestPkt *)msg)->getLts();
            processRequest((RequestPkt *)msg);
        }

        return;
    }

    if (logicSlotCnt < ARSlot + BCSlot && logicSlotCnt >= BCSlot)
    {
        if (REQ_PKT_TYPE == msg->getKind())
            failedSlots[logicSlotCnt - BCSlot] = true;

        EV << "Detected collision in mini-slot # " << logicSlotCnt << " transmitted @" << txSlot << "\n";
        EV << "Cycle "<< cycleCnt << "\n";
        txSlot = -1;
    }
}

void Server::processJoin(JoinPkt* msg)
{
    int pid = jl->allocatePID(msg->getMac());
    EV << "Allocated PID " << pid << " to MAC " << msg->getMac() << "\n";
    jl->addJointoBCS(bcs_pkt, pid, msg->getMac());
}

void Server::processRequest(RequestPkt *msg)
{
    int pid = msg->getPid();
    char eve[90] = {0};

    int reqFrames = msg->getFrames();

    // this request shall be processed in downMessage
    sc->addDataRequest(pid, reqFrames, uniform(0.0, 1.0, 1), eve);

    EV << eve;

    // mark PID as "Given" if it appears as "Offered" (later "Offered" PIDs would run a timeout)
    // TODO: emit 1 here to measure the Join time vs #nodes on a simulation time scale
    jl->confirmGivenPID(pid);

}

int Server::getMAC()
{
    return (getId() + 52295);
}

void Server::refreshDisplay() const
{
    getDisplayString().setTagArg("t", 2, "#808000");
    char str[80] = {0};
    sprintf(str, "Cycle %d Access:%d Data:%d\n\t\t%x/Bytes:%d\n", cycleCnt, ARSlot, SSlot, myMAC, queue->getByteLength());
    getDisplayString().setTagArg("i", 1, "red");
    getDisplayString().setTagArg("t", 0, (const char *)str);
}

}; //namespace
