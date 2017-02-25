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
}

Server::~Server()
{
    cancelAndDelete(slotEvent);
    delete bcs_pkt;
}

void Server::initialize()
{
    server = getModuleByPath("server");
    if (!server)
        throw cRuntimeError("server not found");

    collisionsBase  = registerSignal("collisionsAtBase");
    allocatedBps = registerSignal("allocatedBps");
    requestedBps = registerSignal("requestedBps");

    txRate          = par("txRate");
    slotTime        = par("slotTime");
    maxCycleSlots   = par("cycleSlots");
    numHosts        = par("numHosts");
    ARSmin          = par("ARSmin");
    ARSmax          = par("ARSmax");
    slotBytes       = par("slotBytes");
    backOff         = par("backOff");
    maxPGBK         = par("maxPGBK");
    //BCSlot          = par("BCSlot");

    if (backOff == (int)BACKOFF_HARMONIC)   // for HarmonicBackOff find the smallest size window
        ARSmax = ARSmin;

    ARSlot = ARSmin;

    initFailSlots(ARSlot);
    cycleSlots = ARSlot + 1/*BCSlot*/;
    SSlot = 0;  // no data at the start
    cycleCnt = 0;

    jl = new JoinLeave(bcs_pkt, numHosts);
    sc = new Scheduler(numHosts, maxCycleSlots, ARSlot + 1, maxPGBK);

    pid = PID_PB;

    srand(getId());

    logicSlotCnt = 0;

    scheduleAt(getNextSlotTime(), slotEvent);
}

void Server::handleMessage(cMessage *msg)
{
    // time slot tick event
    if (msg->isSelfMessage())
    {
        if (0 == logicSlotCnt % cycleSlots)  // one cycle passed
        {
            logicSlotCnt = 0;
            cycleCnt++;
        }

        if (logicSlotCnt == 0) // may always be sent from ts0
        {
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

    // Data allocation
    sc->allocate();
    emit(allocatedBps, 8 * slotBytes * sc->getNumOfAllocatedFrames());
    emit(requestedBps, 8 * slotBytes * sc->getNumOfRequestedFrames());
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

    // Handle piggybacked part of packet
    pkt->setPgbksArraySize(numHosts);
    for (int i = 0; i < numHosts; i++)
        pkt->setPgbks(i, sc->getPGBKCnt(i));

    SSlot = sc->getNeededDataFrames();

    cycleSlots = 1/*BCSlot*/ + ARSlot + SSlot;
    if (cycleSlots > maxCycleSlots)
    {
        cycleSlots = maxCycleSlots;
        SSlot = cycleSlots - 1/*BCSlot*/ - ARSlot;
    }

    pkt->setCycleSlots(cycleSlots);

    // fill in failed slots from last cycle
    pkt->setFailedSlotsArraySize(ARSlot);
    for (int i = 0; i < ARSlot; i++)
        pkt->setFailedSlots(i, failedSlots[i]);

    //TODO: add errors to swap ---> p->setBitError(false);

    for (int i = 0; i < numHosts; i++)
    {
        cMessage *copy = ((cMessage *)pkt)->dup();
        send(copy, "out", i);
    }

    // Initialize failed slot information for next cycle
    initFailSlots(ARSlot);
    sc->clearRequests(maxCycleSlots, ARSlot + 1/*BCSlot*/);
    sc->clearAllocations();
    for (int i = 0; i < max_alc; i++)
    {
        pkt->setAlloc_pids(i, EMPTY_PID);
        pkt->setAlloc_frames(i, 0);
    }

}

void Server::initFailSlots(int slots)
{
    if (failedSlots != NULL)
        delete failedSlots;

    failedSlots = new bool[slots];

    for (int i = 0; i < slots; i++)
        failedSlots[i] = false;
}

void Server::updateARSlot()
{
    int f = 0;

    if (backOff != (int)BACKOFF_HARMONIC)
    {
        for (int i = 0; i < ARSlot; i++)
           if (failedSlots[i])
              f++;

        if (f >= ARSlot/3)        // increase
        {
            if (ARSlot < ARSmax)
                ARSlot++;
        }
        else   // decrease
        {
            if (ARSlot > ARSmin)
                ARSlot--;
        }
    }
}

void Server::receiveRemote(cPacket* msg)
{
    static int tmpLogicSlot = -1;

    if (tmpLogicSlot != logicSlotCnt)
    {
        tmpLogicSlot = logicSlotCnt;

        if (JOIN_PKT_TYPE == msg->getKind())
        {
            processJoin((JoinPkt *)msg);
        }
        else if (REQ_PKT_TYPE == msg->getKind())
        {
            processRequest((RequestPkt *)msg);
        }

        emit(collisionsBase, 0);

        return;
    }

    EV << "Detected collision in mini-slot # " << logicSlotCnt-1 << "\n";
    emit(collisionsBase, 1);

    if (logicSlotCnt <= ARSlot && logicSlotCnt > 0)
        failedSlots[logicSlotCnt-1] = true;
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

    int reqBytes = msg->getBytes();
    int reqFrames = reqBytes / slotBytes + ((reqBytes % slotBytes) ? 1 : 0);

    // this request shall be processed in downMessage
    sc->addDataRequest(pid, reqFrames, uniform(0.0, 1.0, 1), eve);

    EV << eve;

    // mark PID as "Given" if it appears as "Offered" (later "Offered" PIDs would run a timeout)
    // TODO: emit 1 here to measure the Join time vs #nodes on a simulation time scale
    jl->confirmGivenPID(pid);

}

void Server::refreshDisplay() const
{
    getDisplayString().setTagArg("t", 2, "#808000");
    char str[40] = {0};
    sprintf(str, "Cycle %d Access:%d Data:%d", cycleCnt, ARSlot, SSlot);
    getDisplayString().setTagArg("i", 1, "red");
    getDisplayString().setTagArg("t", 0, (const char *)str);
}

}; //namespace
