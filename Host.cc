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
    joinPkt = new JoinPkt("PR_Join");
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

    inNetworkState = ALONE;
    syncState = BOOT;
    bootDelay = rand() % randomStart;
    logicSlotCnt = rand() % cycleSlots;
    pid = 0;
    reqSlot = -1;
    cycleCnt = 0;
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
        {
            logicSlotCnt = 0;
            EV << "New cycle:" << cycleCnt++ << "\n";
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
            if (ALONE == inNetworkState)
            {
                if (0 == logicSlotCnt)
                    reqSlot = findUpJoinSlot();

                if (reqSlot >= 0 && reqSlot == logicSlotCnt)
                {
                    EV << "Sending Join Request from " << getMAC() << " in slot " << reqSlot << "\n";
                    upJoinRequest(joinPkt);
                    reqSlot = -1;
                }
            }
        }

        scheduleAt(getNextSlotTime(), msg);
        ++logicSlotCnt;
        return;
    }

    // handle message from base
    this->receiveBase(msg);
}

simtime_t Host::getNextSlotTime()
{
    simtime_t t = simTime();

    if (BOOT == syncState)  // creates a slot-fraction time offset, random and different for each host
    {
        t += slotTime + (slotTime * (double)(rand() % 1000) / 1000.0);
        syncState = BOOTING;
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

    cycleSlots  = pkt->getCycleSlots();
    ARSlot      = pkt->getARS();

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
}

void Host::upJoinRequest(JoinPkt* pkt)
{
    pkt->setMac(getMAC());
    cMessage *copy = ((cMessage *)pkt)->dup();
    send(copy, "out");
}

int Host::getMAC()
{
    return (getId() + 52295);
}

int Host::findUpJoinSlot()
{
    return ( 1 + rand() % ARSlot );
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
        getDisplayString().setTagArg("t", 0, "BOOTED");
    }
    else if (syncState == TSYNC)
    {
        getDisplayString().setTagArg("i", 1, "yellow");
        getDisplayString().setTagArg("t", 0, "TIME-SYNCED");
    }
    else if (syncState == LSYNC)
    {
        getDisplayString().setTagArg("i", 1, "green");
        getDisplayString().setTagArg("t", 0, "SYNCED");
    }
}


}; //namespace
