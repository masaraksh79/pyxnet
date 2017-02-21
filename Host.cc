//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include "Host.h"
#include "pkt_m.h"

namespace pyxis {

Define_Module(Host);

Host::Host()
{
    slotEvent = new cMessage("Slot");
    joinPkt = new JoinPkt("PR_Join",JOIN_PKT_TYPE);
    requestPkt = new RequestPkt("PR_Rq",REQ_PKT_TYPE);
    newPkt = new cMessage;
    queue = new cPacketQueue("Buffer");
}

Host::~Host()
{
    cancelAndDelete(slotEvent);
    cancelAndDelete(joinPkt);
    cancelAndDelete(requestPkt);
    cancelAndDelete(newPkt);

    while (!queue->isEmpty())
    {
        cPacket* p = queue->pop();
        delete p;
    }

    delete queue;
}

void Host::initialize()
{
    server = getModuleByPath("server");
    if (!server)
        throw cRuntimeError("server not found");

    queueLength = registerSignal("queueLenPackets");
    collCnt = registerSignal("collisionsAtHost");

    txRate          = par("txRate");
    slotTime        = par("slotTime");
    radioDelay      = par("radioDelay");
    cycleSlots      = par("cycleSlots");
    randomStart     = par("randomStart");
    iaTime          = &par("iaTime");
    dataLen         = par("dataLen");
    slotBytes       = par("slotBytes");
    backOff         = par("backOff");

    srand(getId());

    inNetworkState = ALONE;
    syncState = BOOT;
    bootDelay = rand() % randomStart;
    logicSlotCnt = rand() % cycleSlots;


    pid = EMPTY_PID;
    myMAC = this->getMAC();

    reqSlot = -1;
    collisionCnt = 0;
    cycleCnt = 0;
    isSynced = false;
    slotRx = 0;
    slotUs = uniform(0, 0.0, 1.0) * slotTime.dbl();

    gate("in")->setDeliverOnReceptionStart(true);

    scheduleAt(getNextSlotTime(), slotEvent);   // mini-slot event
    scheduleAt(getNextPktTime(), newPkt);       // event to add new packet into queue
}

void Host::handleMessage(cMessage *msg)
{
    // time slot tick event
    if (msg->isSelfMessage())
    {
        //TODO: need to see what doing with fragmentation
        if (newPkt == msg)  // new fifo packet
        {
            queue->insert(new cPacket("Scada", 0, dataLen));
            scheduleAt(getNextPktTime(), newPkt);
            return;
        }

        if (0 == logicSlotCnt % cycleSlots)  // one cycle passed
        {
            logicSlotCnt = 0;
            EV << "New cycle:" << cycleCnt++ << "\n";
            emit(queueLength, queue->getLength());
        }

        slotUs = simTime();

        if (bootDelay)
        {
            bootDelay--;
        }
        else if (syncState == BOOTING)
        {
            EV << "Finished booting MAC " << getMAC() << "\n";
            syncState = UNSYNC;
        }

        if (UNSYNC < syncState) // normal or partial synchronized state
        {
            if (0 == logicSlotCnt)
                reqSlot = findUpSlot();

            if (reqSlot >= 0 && reqSlot == logicSlotCnt)
            {
                if (ALONE == inNetworkState)
                {
                    EV << "Sending Join Request from " << getMAC() << " in slot " << reqSlot << "\n";
                    upJoinRequest(joinPkt);
                }
                else if (queue->getLength()) // Joined (only sends if data is in the queue)
                {
                    EV << "Sending Request from " << getMAC() << " in slot " << reqSlot << "\n";
                    upRequest(requestPkt);
                }
            }
        }

        scheduleAt(getNextSlotTime(), msg);
        ++logicSlotCnt;
        return;
    }

    // handle message from base
    this->receiveBase(msg);
    delete msg;
}

simtime_t Host::getNextSlotTime()
{
    simtime_t t = simTime();

    if (BOOT == syncState)  // creates a slot-fraction time offset, random and different for each host
    {
        t += slotTime + (slotTime * uniform(0, 0.0, 1.0));
        syncState = BOOTING;
        return t;
    }
    else
    {
        return (t + slotTime);
    }
}

simtime_t Host::getNextPktTime()
{
    return (simTime() + iaTime->doubleValue());
}

void Host::receiveBase(cMessage* msg)
{
    static int prevARSlot = -1;
    BasePkt *pkt = (BasePkt *)msg;

    slotRx = simTime();

    if (bootDelay > 0)
        return;

    cycleSlots  = pkt->getCycleSlots();
    ARSlot      = pkt->getARS();

    if (prevARSlot != ARSlot)
    {
        prevARSlot = ARSlot;
        collisionCnt = 0;
    }


    if (UNSYNC == syncState)
    {
        if (slotRx != slotUs)
        {
            simtime_t tmpSlotUs = slotUs;
            int tmpLogicSlotCnt = logicSlotCnt;

            logicSlotCnt = pkt->getLts();
            EV << "MAC " << getMAC() << " logical slot now is " << logicSlotCnt << "\n";

            //TODO: use radioDelay for difference error!

            if (slotRx > slotUs) // if base time is later than remote then jump up by the difference
                slotUs += slotRx;
            else            // otherwise, jump by one slot and return by the difference t_rem-t_base
                slotUs = slotUs + slotTime - slotRx;

            if (hasGUI())
            {
                char buf[64];
                sprintf(buf, "Corrected %lf->%lf, Slot %d->%d", tmpSlotUs.dbl(), slotUs.dbl(), tmpLogicSlotCnt, logicSlotCnt);
                bubble(buf);
            }

            // reschedule
            cancelEvent(slotEvent);
            scheduleAt(slotUs, slotEvent);
        }

        syncState = LSYNC;      // assume LSYNC and TSYNC automatically (TODO: might only be TSYNC is packet is bad)
    }

    if (UNSYNC < syncState)
    {
       // handle the advertisement about collision from PB to back-off
       this->doBackOff(pkt);

       if (ALONE == inNetworkState)
           this->processPBJoin(pkt);
       else
           this->processPBControl(pkt);
    }
}

void Host::upJoinRequest(JoinPkt* pkt)
{
    pkt->setMac(getMAC());
    cMessage *copy = ((cMessage *)pkt)->dup();
    send(copy, "out");
}

void Host::upRequest(RequestPkt* pkt)
{
    if (pid == EMPTY_PID)
    {
        EV << "Should not try sending request if PID=0!\n";
        return;
    }

    pkt->setPid(pid);
    pkt->setBytes(queue->getBitLength());
    EV << "Requested to transmit " << queue->getLength() << " pkts\n";
    cMessage *copy = ((cMessage *)pkt)->dup();
    send(copy, "out");
}

int Host::getMAC()
{
    return (getId() + 52295);
}

int Host::findUpSlot()
{
    if (backOff != (int)BACKOFF_RAMPUP && collisionCnt > 0)
    {
        double harmonic = (1.0 / (1.0 + collisionCnt));
        double heads = uniform(1, 0.0, 1.0);

        if (heads <= harmonic)
        {
            EV << "MAC " << getMAC() << " will capture a slot!\n";
            return ( 1 + rand() % ARSlot );
        }
        else
        {
            EV << "MAC " << getMAC() << " avoided request due collisions\n";
            return -1;
        }
    }

    return ( 1 + rand() % ARSlot );
}

/* Harmonic backOff
 * ----------------
 * Will transmit the next request (or join request)
 * with probability 1/(1+k) where k is the last counted
 * number of collisions. Collisions are reported by the base
 * in BCS and if on my last AR slot there were none do
 * --cnt until 0 otherwise cnt++;
 * */

void Host::doBackOff(BasePkt* pkt)
{
    for (int i = 0; i < ARSlot; i++)
    {
        if (i == reqSlot)
        {
            if (pkt->getFailedSlots(i))
            {
                collisionCnt++;
                EV << "MAC " << getMAC() << " will backOff from " << (1.0/(1.0+collisionCnt)) << "\n";
            }
            else if (collisionCnt)  // return from backing off
            {
                collisionCnt--;
            }

            emit(collCnt, collisionCnt);
            break;
        }
    }
}

void Host::processPBJoin(BasePkt* pkt)
{
    for (int i = 0; i < pkt->getMacsArraySize(); i++)
    {
        if (pkt->getMacs(i) == getMAC())
        {
            pid = pkt->getPids(i);
            inNetworkState = JOINED;
            EV << "Received allocation for PID " <<  pid << "!\n";
            break;
        }
    }
}

void Host::processPBControl(BasePkt* pkt)
{
    cPacket* p;

    for (int i = 0; i < pkt->getAlloc_pidsArraySize(); i++)
    {
        if (pid == pkt->getAlloc_pids(i))
        {
            int alc = pkt->getAlloc_frames(i);
            while (alc && !queue->isEmpty())
            {
                p = queue->pop();
                delete p;
                alc--;
            }
        }
    }
}

void Host::refreshDisplay() const
{
    getDisplayString().setTagArg("t", 2, "#808000");
    if (syncState == BOOT)
    {
        getDisplayString().setTagArg("i", 1, "");
        getDisplayString().setTagArg("t", 0, "");
    }
    if (syncState == UNSYNC)
    {
        getDisplayString().setTagArg("i", 1, "red");
        char pidstr[20] = {0};
        sprintf(pidstr, "BOOTED (%d)", pid, myMAC);
        getDisplayString().setTagArg("t", 0, (const char *)pidstr);
    }
    else if (syncState == TSYNC)
    {
        getDisplayString().setTagArg("i", 1, "yellow");
        char pidstr[20] = {0};
        sprintf(pidstr, "TIME-SYNCED (%d)", pid, myMAC);
        getDisplayString().setTagArg("t", 0, (const char *)pidstr);
    }
    else if (syncState == LSYNC)
    {
        getDisplayString().setTagArg("i", 1, "green");
        char pidstr[20] = {0};

        if (pid == EMPTY_PID)
        {
            sprintf(pidstr, "SYNCED (%d)", myMAC);
            getDisplayString().setTagArg("t", 0, (const char *)pidstr);
        }
        else
        {
            sprintf(pidstr, "%d/%d\nBytes:%lu", pid, myMAC, queue->getByteLength());
            getDisplayString().setTagArg("t", 0, (const char *)pidstr);
        }

    }
}


}; //namespace
