//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifndef __ALOHA_HOST_H_
#define __ALOHA_HOST_H_

#include <omnetpp.h>
#include "pkt_m.h"

using namespace omnetpp;

namespace pyxis {

/**
 * Pyxis remote host; see NED file for more info.
 */
class Host : public cSimpleModule
{
  private:
    // parameters
    simtime_t radioDelay;
    int cycleSlots, ARSlot, bootDelay, randomStart;
    int reqSlot, collisionCnt;
    double txRate;
    simtime_t slotRx, slotUs;
    simtime_t slotTime;
    cQueue queue;

    // state variables, event pointers etc
    cModule *server;
    cMessage *slotEvent;
    JoinPkt* joinPkt;
    // time and logic synchronization
    // first the unit boots and starts with its random time slot
    // then unit automatically drops into UNSYNC mode
    // Unit that has received a packet from another valid PID acquires TSYNC
    // and if the packet content is sound the LSYNC (there might be the case)
    // where UNSYNC->LSYNC however if packet has bad CRC then only UNSYNC->TSYNC
    enum { BOOT = 0, BOOTING, UNSYNC, TSYNC, LSYNC } syncState;
    enum { ALONE = 0, JOINED } inNetworkState;
    int pid, logicSlotCnt;     // Pyxis node ID and logical slot counter
    long long cycleCnt;
    bool isSynced;

  public:
    Host();
    virtual ~Host();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void refreshDisplay() const override;
    void receiveBase(cMessage* msg);
    void upJoinRequest(JoinPkt* pkt);
    int getMAC();
    void backOff(BasePkt* pkt);
    int findUpJoinSlot();
    simtime_t getNextSlotTime();
};

}; //namespace

#endif

