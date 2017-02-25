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

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <omnetpp.h>

namespace pyxis {

#define MAX_ALLOCATIONS 25

typedef struct
{
    int pid;
    int frames;
    int sfr;        // sticky frames, same as .frames just not nullified by ->allocate
}
req_t;

typedef struct
{
    int pid;
    int frames;
}
alc_t;

class Scheduler {
public:
    Scheduler(int, int, int, int );  /* args: hosts, cycle slots, access slots (AR+1), max PGBK allowed */
    virtual ~Scheduler();
    void addDataRequest(int pid, int frames, double rng, char* eve);
    void clearRequests(int CS, int AS);
    void clearAllocations();
    int getNumOfAllocated();
    int getAllocatedPID(int id);
    int getAllocatedFrames(int id);
    int getNeededDataFrames();
    void allocate();
    int getNumOfAllocatedFrames();
    int getNumOfRequestedFrames();
    bool emptyRequests();
    int getPGBKCnt(int pid);
private:
    int numHosts;
    int numReqFrames, numAlcFrames;
    int *numPGBK;
    int numMiniSlots;
    int numFrames;      // number of frames requested from start of AR
    int maxFrames;
    int maxPGBK;
    req_t* requests;
    alc_t* allocations;
    int reqPLeft, reqPRight;
    // requests operations
    bool allocateItem(int r);
};

} /* namespace pyxis */

#endif /* SCHEDULER_H_ */
