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
        double txRx @unit(s);  				// transmission - reception total switching per slot
        double slotTime @unit(s);  		// mini-slot time
        @display("bgb=5000,3000;bgi=maps/usa,s;bgg=1000,2,grey95;bgu=km");
    submodules:
        server: Server
        {
           numHosts = numHosts; 
           txRx = txRx;
           slotTime = slotTime;		
           cycleSlots = cycleSlots;
           slotBytes = slotBytes;
           firstSlotBytes = firstSlotBytes;
           backOff = backOff;
        };
        host[numHosts]: Host
        {
            numHosts = numHosts;
            txRx = txRx;
            slotTime = slotTime;		
           cycleSlots = cycleSlots;
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

