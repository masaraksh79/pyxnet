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
        int BCSlot;
        int ARSmin;
        int ARSmax;
        volatile int dataLen;
        int maxPGBK;
        int slotBytes;
        int firstSlotBytes;
        double txRx @unit(s);     
        //volatile double iaTime @unit(s);  // packet interarrival time
        double slotTime @unit(s);         
        volatile double iaTime @unit(s);  	
        @display("i=device/antennatower_l;p=2000,300");
        @statistic[collisionsAtBase](record=(mean);title="Proportion of collided slots in ARS");
        @signal[collisionsAtBase](type="double");
        @statistic[allocatedBps](record=(mean);title="Number of allocated frames per cycle");
        @signal[allocatedBps](type="long");
        @statistic[requestedBps](record=(mean);title="Number of recvd request bps per cycle");
        @signal[requestedBps](type="long");
        @statistic[efficiency](record=(mean);title="Average cycle efficiency");
        @signal[efficiency](type="double");
        @statistic[business](record=(mean);title="Average cycle business");
        @signal[business](type="double");
                 gates:
            input in[numHosts];
            output out[numHosts];
}

