//
// Pyxis network consists of Base and Remotes
// Pyxis protocol allows remote to become relay
//
network Pyxis
{
    parameters:
        int backOff;
        int numHosts; 								// number of hosts
        int cycleSlots;									// initially assumed cycle (only AS - access slots)
        int firstSlotBytes;							// slots belong to first packet with PHY header
        int slotBytes;									// each additional overlapping slot packet (incl. tx-rx time)
        int BCSlot;
        double txRate @unit(bps);  			// transmission rate
        double slotTime @unit(ms);  		// mini-slot time
        @display("bgb=5000,3000;bgi=maps/usa,s;bgg=1000,2,grey95;bgu=km");
        //@display("bgi=background/terrain,s");
    submodules:
        server: Server
        {
           numHosts = numHosts; 
           txRate = txRate;
           slotTime = slotTime;		
           cycleSlots = cycleSlots;
           slotBytes = slotBytes;
           BCSlot = BCSlot;
           backOff = backOff;
        };
        host[numHosts]: Host
        {
            numHosts = numHosts;
            txRate = txRate;
            slotTime = slotTime;		
           cycleSlots = cycleSlots;
           BCSlot = BCSlot;
           slotBytes = slotBytes;
           firstSlotBytes = firstSlotBytes;
           backOff = backOff;
        }; 
	connections:
    	for i=0..numHosts-1 { 
        	server.out[i] --> { delay=1us; } --> host[i].in;
        	server.in[i] <-- { delay=1us; } <-- host[i].out;
		}
}

