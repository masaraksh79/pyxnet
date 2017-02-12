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

using namespace omnetpp;

namespace pyxis {

class Server : public cSimpleModule
{
    private:
      // parameters
      simtime_t radioDelay;
      int cycleSlots, ARSlot;
      int numHosts;
      double txRate;
      simtime_t slotTime;
      cQueue queue;

      // state variables, event pointers etc
      cModule *server;
      cMessage *slotEvent;
      BasePkt* bcs_pkt;
      // time and logic synchronization
      // first the unit boots and starts with its random time slot
      // then unit automatically drops into UNSYNC mode
      // Unit that has received a packet from another valid PID acquires TSYNC
      // and if the packet content is sound the LSYNC (there might be the case)
      // where UNSYNC->LSYNC however if packet has bad CRC then only UNSYNC->TSYNC
      int pid, lscnt;     // Pyxis node ID and logical slot counter
      int pkCounter;

    public:
      Server();
      virtual ~Server();

    protected:
      virtual void initialize() override;
      virtual void handleMessage(cMessage *msg) override;
      simtime_t getNextSlotTime();
      void downMessage(BasePkt *pkt);
};

}; //namespace

#endif

