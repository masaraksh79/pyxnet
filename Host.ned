//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


//
// A computer in the ALOHAnet network.
//
simple Host
{
    parameters:
        int backOff;
        int numHosts;
        int randomStart;
        volatile int dataLen;									// typical packet len from Host data source (bytes)
        int slotBytes;
        int firstSlotBytes;
        int cycleSlots;									// dummy inited but is received from PB
        double txRx @unit(s);                // transmission rate
        double radioDelay @unit(s);       // propagation delay of radio link
        volatile double iaTime @unit(s);  // packet interarrival time
        double slotTime @unit(s);         
        @display("i=device/smallrouter;p=1200,800,ri,1000,1000 ");
        //@statistic[queueLenPackets](record=vector(mean);title="Transmit Queue Length");
        @signal[queueLenPackets](type="long");
        //@statistic[collisionsAtHost](record=vector(mean);title="Local Detected Collisions");
        @signal[collisionsAtHost](type="long");
     gates:
        input in;
        output out;        
}

