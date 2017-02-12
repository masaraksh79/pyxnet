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

    pid = 1;

    srand(getId());

    lscnt = 0;

    pkCounter = 0;

    scheduleAt(getNextSlotTime(), slotEvent);
}

void Server::handleMessage(cMessage *msg)
{
    // time slot tick event
    if (msg->isSelfMessage())
    {
        if (0 == lscnt % cycleSlots)  // one cycle passed
            lscnt = 0;

        if (lscnt == 0) // may always be sent from ts0
            this->downMessage(bcs_pkt);

        ++lscnt;

        scheduleAt(getNextSlotTime(), msg);
        return;
    }

}

simtime_t Server::getNextSlotTime()
{
    simtime_t t = simTime() + slotTime;
    return t;
}

void Server::downMessage(BasePkt *pkt)
{
    pkt->setPid(pid);
    pkt->setLts(lscnt);
    pkt->setCycleSlots(cycleSlots);

    //TODO: add errors to swap ---> p->setBitError(false);

    for (int i = 0; i < numHosts; i++)
    {
        cMessage *copy = ((cMessage *)pkt)->dup();
        send(copy, "out", i);
    }
}

}; //namespace
