//
// Pyxis network consists of Base and Remotes
// Pyxis protocol allows remote to become relay
//
network Pyxis
{
    parameters:
        int numHosts; 								// number of hosts
        int cycleSlots;									// initially assumed cycle (only AS - access slots)
        double txRate @unit(bps);  			// transmission rate
        double slotTime @unit(ms);  		// mini-slot time
        @display("bgi=background/terrain,s");
    submodules:
        server: Server
        {
           numHosts = numHosts; 
           txRate = txRate;
           slotTime = slotTime;		
           cycleSlots = cycleSlots;
        };
        host[numHosts]: Host
        {
            numHosts = numHosts;
            txRate = txRate;
            slotTime = slotTime;		
           cycleSlots = cycleSlots;
        }; 
	connections:
    	for i=0..numHosts-1 { 
        	server.out[i] --> { delay=1us; } --> host[i].in;
        	server.in[i] <-- { delay=1us; } <-- host[i].out;
		}
}

