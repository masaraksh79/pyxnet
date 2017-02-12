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
#include <stdlib.h>

namespace pyxis {

Define_Module(Host);

Host::Host()
{
    slotEvent = new cMessage("Slot");
}

Host::~Host()
{
    cancelAndDelete(slotEvent);
}

void Host::initialize()
{
    server = getModuleByPath("server");
    if (!server)
        throw cRuntimeError("server not found");

    txRate          = par("txRate");
    slotTime        = par("slotTime");
    radioDelay      = par("radioDelay");
    cycleSlots      = par("cycleSlots");
    randomStart     = par("randomStart");

    srand(getId());

    bootState = BOOT;
    bootDelay = rand() % randomStart;
    logicSlotCnt = rand() % cycleSlots;
    pid = 0;
    isSynced = false;
    slotRx = 0;
    slotUs = (rand() % 100) / 100.0 * slotTime.dbl();

    gate("in")->setDeliverOnReceptionStart(true);

    scheduleAt(getNextSlotTime(), slotEvent);
}

void Host::handleMessage(cMessage *msg)
{
    // time slot tick event
    if (msg->isSelfMessage())
    {
        if (0 == logicSlotCnt % cycleSlots)  // one cycle passed
            logicSlotCnt = 0;

        slotUs = simTime();

        ++logicSlotCnt;

        if (bootDelay)
            bootDelay--;
        else if (bootState == BOOTING)
        {
            EV << "start delay " << bootDelay << "\n";
            bootState = UNSYNC;
        }

        scheduleAt(getNextSlotTime(), msg);
        return;
    }

    // handle message from base
    this->receiveBase(msg);
}

simtime_t Host::getNextSlotTime()
{
    simtime_t t = simTime();

    if (BOOT == bootState)  // creates a slot-fraction time offset, random and different for each host
    {
        t += slotTime + (slotTime * (double)(rand() % 1000) / 1000.0);
        bootState = BOOTING;
        return t;
    }
    else
    {
        return (t + slotTime);
    }
}

void Host::receiveBase(cMessage* msg)
{
    BasePkt *pkt = (BasePkt *)msg;

    slotRx = simTime();

    if (bootDelay > 0)
        return;

    if (UNSYNC == bootState)
    {
        if (slotRx != slotUs)
        {
            simtime_t tmpslotUs = slotUs;
            int tmplscnt = logicSlotCnt;

            logicSlotCnt = pkt->getLts();

            cycleSlots = pkt->getCycleSlots();

            //TODO: use radioDelay for difference error!

            if (slotRx > slotUs) // if base time is later than remote then jump up by the difference
                slotUs += slotRx;
            else            // otherwise, jump by one slot and return by the difference t_rem-t_base
                slotUs = slotUs + slotTime - slotRx;

            if (hasGUI())
            {
                char buf[64];
                sprintf(buf, "Time %lf->%lf, Slot %d->%d", tmpslotUs.dbl(), slotUs.dbl(), tmplscnt, logicSlotCnt);
                bubble(buf);
            }

            // reschedule
            cancelEvent(slotEvent);
            scheduleAt(slotUs, slotEvent);
        }

        bootState = LSYNC;      // assume LSYNC and TSYNC automatically (TODO: might only be TSYNC is packet is bad)
    }

}

void Host::refreshDisplay() const
{
    getDisplayString().setTagArg("t", 2, "#808000");
    if (bootState == BOOT)
    {
        getDisplayString().setTagArg("i", 1, "");
        getDisplayString().setTagArg("t", 0, "");
    }
    if (bootState == UNSYNC)
    {
        getDisplayString().setTagArg("i", 1, "red");
        getDisplayString().setTagArg("t", 0, "BOOTED");
    }
    else if (bootState == TSYNC)
    {
        getDisplayString().setTagArg("i", 1, "yellow");
        getDisplayString().setTagArg("t", 0, "TIME-SYNCED");
    }
    else if (bootState == LSYNC)
    {
        getDisplayString().setTagArg("i", 1, "green");
        getDisplayString().setTagArg("t", 0, "SYNCED");
    }
}


}; //namespace
