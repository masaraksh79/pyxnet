//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

namespace pyxis;

//
// TODO generated message class
//
packet BasePkt {
    int pid;			// base PID (might be PRR PID)
    int lts;				// logical time-slot
    int cycleSlots;	// adv next cycle slots
    int ARS;			// Access Request Slot len
    int macs[];		// a combination of MAC+PID	
    int pids[];		// in an array for single or group PID allocation
    bool failedSlots[];		// in an array for slots with detected collision
}

packet JoinPkt {
    int mac;				// a replacement of MAC address in real nodes
}
