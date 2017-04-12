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
#include "JoinLeave.h"
#include "PyxisDefs.h"
#include "Defragmenter.h"

using namespace omnetpp;

namespace pyxis {

/**
 * Pyxis remote host; see NED file for more info.
 */
class Host : public cSimpleModule
{
  private:
    // parameters
    simsignal_t queueLength;
    simsignal_t collCnt;

    simtime_t radioDelay;
    int cycleSlots, ARSlot, bootDelay, randomStart;
    int BCSlot;
    int reqSlot, collisionCnt, slotBytes, firstSlotBytes;
    int dataLen, numHandledFrames;
    int myMAC;
    simtime_t slotRx, slotUs;
    simtime_t slotTime, txRx;
    cPacketQueue *queue;
    cPar *iaTime;

    Defragmenter *df;

    // state variables, event pointers etc
    cMessage *slotEvent;
    JoinPkt* joinPkt;
    RequestPkt* requestPkt;
    cMessage* newPkt;
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
    int backOff;
    int PGBK;

  public:
    Host();
    virtual ~Host();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void refreshDisplay() const override;
    void receiveBase(cMessage* msg);
    void upJoinRequest(JoinPkt* pkt);
    void upRequest(RequestPkt* pkt);
    int getMAC();
    void doBackOff(BasePkt* pkt);
    int findUpSlot();
    void processPBJoin(BasePkt* pkt);
    void processPBControl(BasePkt* pkt);
    simtime_t getNextSlotTime();
    simtime_t getNextPktTime();
};

}; //namespace

#endif

