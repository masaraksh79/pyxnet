//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

//
// The central computer in the ALOHAnet network.
//
simple Server
{
    parameters:
        int backOff;
        int numHosts;
        int cycleSlots;
        int ARSmin;
        int ARSmax;
        int slotBytes;
        double txRate @unit(bps);          // transmission rate
        //volatile int pkLenBits @unit(b);  // packet length in bits
        //volatile double iaTime @unit(s);  // packet interarrival time
        double slotTime @unit(s);         
        @display("i=device/antennatower_l;p=2000,300");
        @statistic[collisionsAtBase](record=vector(mean);title="Number of uplink collisions");
        @signal[collisionsAtBase](type="long");
        @statistic[allocatedBps](record=vector(mean);title="Number of allocated frames per cycle");
        @signal[allocatedBps](type="long");
        @statistic[requestedBps](record=vector(mean);title="Number of requested frames per cycle");
        @signal[requestedBps](type="long");
         gates:
            input in[numHosts];
            output out[numHosts];
}

