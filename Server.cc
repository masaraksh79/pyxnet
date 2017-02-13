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

    txRate          = par("txRate");
    slotTime        = par("slotTime");
    cycleSlots      = par("cycleSlots");
    numHosts        = par("numHosts");
    ARSlot          = par("ARSInitial");

    pid = 1;

    srand(getId());

    logicSlotCnt = 0;
    initFailSlots(ARSlot);

    scheduleAt(getNextSlotTime(), slotEvent);
}

void Server::handleMessage(cMessage *msg)
{
    // time slot tick event
    if (msg->isSelfMessage())
    {
        if (0 == logicSlotCnt % cycleSlots)  // one cycle passed
            logicSlotCnt = 0;

        if (logicSlotCnt == 0) // may always be sent from ts0
            this->downMessage(bcs_pkt);

        ++logicSlotCnt;

        scheduleAt(getNextSlotTime(), msg);
        return;
    }

    receiveRemote((cPacket *)msg);

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
    pkt->setPid(pid);
    pkt->setLts(logicSlotCnt);
    pkt->setCycleSlots(cycleSlots);
    pkt->setARS(ARSlot);
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
    this->initFailSlots(ARSlot);
}

void Server::initFailSlots(int slots)
{
    if (failedSlots != NULL)
        delete failedSlots;

    failedSlots = new bool[slots];

    for (int i = 0; i < slots; i++)
        failedSlots[i] = false;

    rxAtSlot = 0;   // used to detect whether received more than one remote in same AR Slot
}

void Server::receiveRemote(cPacket* msg)
{
    static int tmpLogicSlot = -1;

    EV << "PB Rx in mini-slot # " << logicSlotCnt << "\n";

    if (tmpLogicSlot != logicSlotCnt)
    {
        tmpLogicSlot = logicSlotCnt;
        processJoin((JoinPkt *)msg);
        return;
    }

    EV << "Detected collision in mini-slot # " << logicSlotCnt << "\n";

    if (logicSlotCnt <= ARSlot && logicSlotCnt > 0)
        failedSlots[logicSlotCnt-1] = true;
}

void Server::processJoin(JoinPkt* msg)
{
    // TODO: allocate PID
}

}; //namespace
