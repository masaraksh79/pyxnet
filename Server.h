//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifndef __PYXIS_BASE_H_
#define __PYXIS_BASE_H_

#include <omnetpp.h>
#include "pkt_m.h"
#include "JoinLeave.h"
#include "PyxisDefs.h"
#include "Scheduler.h"
#include "Defragmenter.h"

using namespace omnetpp;

namespace pyxis {

class Server : public cSimpleModule
{
    private:
      // parameters
      simsignal_t collisionsBase;
      simsignal_t allocatedBps;
      simsignal_t requestedBps;
      simsignal_t efficiency;
      simsignal_t business;
      cPar *iaTime;

      simtime_t radioDelay;
      int cycleCnt, cycleSlots, maxCycleSlots, slotBytes, firstSlotBytes;
      int ARSlot, ARSmin, ARSmax, SSlot;
      int BCSlot, dataLen;
      int numHosts;
      int myMAC;
      bool* failedSlots;
      bool* reservedSlots;
      simtime_t slotTime, txRx;
      cPacketQueue *queue;

      // state variables, event pointers etc
      cModule *server;
      cMessage *slotEvent;
      cMessage *newPkt;
      BasePkt* bcs_pkt;
      // time and logic synchronization
      // first the unit boots and starts with its random time slot
      // then unit automatically drops into UNSYNC mode
      // Unit that has received a packet from another valid PID acquires TSYNC
      // and if the packet content is sound the LSYNC (there might be the case)
      // where UNSYNC->LSYNC however if packet has bad CRC then only UNSYNC->TSYNC
      int pid, logicSlotCnt, tmpSlotCnt;     // Pyxis node ID and logical slot counter
      int backOff, maxPGBK;

      //Supporting lib classes
      JoinLeave *jl;
      Scheduler *sc;
      Defragmenter *df;

    public:
      Server();
      virtual ~Server();

    protected:
      virtual void initialize() override;
      virtual void handleMessage(cMessage *msg) override;
      virtual void refreshDisplay() const override;
      simtime_t getNextSlotTime();
      simtime_t getNextPktTime();
      void downMessage(BasePkt *pkt);
      void initEvalSlots(int slots);
      void updateARSlot();
      void receiveRemote(cPacket* msg);
      void processJoin(JoinPkt* msg);
      void processRequest(RequestPkt *msg);
      int numOfTxDBits(int frames);
      int getMAC();
      void PBRequest();
      void PBScheduleData();

};

}; //namespace

#endif

