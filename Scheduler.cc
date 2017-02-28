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

#include <Scheduler.h>
#include "JoinLeave.h"

namespace pyxis {

Scheduler::Scheduler(int hosts, int CS, int AS, int maxPGBKcnt)
{
    numHosts = hosts;
    numFrames = 0;
    numMiniSlots = CS - AS;
    maxFrames = numMiniSlots;
    maxPGBK = maxPGBKcnt;

    requests = new req_t[numHosts + 1]; /* +1 for downlink */
    for (int i = 0; i <= numHosts; i++)
    {
        requests[i].pid = EMPTY_PID;
        requests[i].frames = 0;
        requests[i].sfr = 0;
    }

    allocations = new alc_t[MAX_ALLOCATIONS];
    for (int i = 0; i < MAX_ALLOCATIONS; i++)
    {
        allocations[i].pid = EMPTY_PID;
        allocations[i].frames = 0;
    }

    numPGBK = new int[numHosts];
    for (int i = 0; i < numHosts; i++)
        numPGBK[i] = 0;

}

Scheduler::~Scheduler()
{
    delete requests;
    delete allocations;
}

void Scheduler::addDataRequest(int pid, int frames, double rng, char* eve)
{
    numFrames += frames;

    // push randomly from the middle

    if (rng <= 0.5)   // upper half placement
    {
        if (reqPRight <= numHosts)
        {
            requests[reqPRight].frames = frames;
            requests[reqPRight].sfr = frames;
            requests[reqPRight].pid = pid;
            sprintf (eve, "Req added to %d for PID %d\n", reqPRight, pid);
            reqPRight++;
        }
        else // module 0 to elms-1
        {
            reqPRight = 0;
            requests[reqPRight].frames = frames;
            requests[reqPRight].sfr = frames;
            requests[reqPRight].pid = pid;
            sprintf (eve, "Req added to %d for PID %d\n", reqPRight, pid);
            reqPRight++;
        }
    }
    else  // lower half placement
    {
        if (reqPLeft >= 0)
        {
            requests[reqPLeft].frames = frames;
            requests[reqPLeft].sfr = frames;
            requests[reqPLeft].pid = pid;
            sprintf (eve, "Req added to %d for PID %d\n", reqPLeft, pid);

            // wrap around
            if (!reqPLeft)
                reqPLeft = numHosts;
            else
                reqPLeft--;
        }
        else
        {
            reqPLeft = numHosts;
            requests[reqPLeft].frames = frames;
            requests[reqPLeft].sfr = frames;
            requests[reqPLeft].pid = pid;
            sprintf (eve, "Req added to %d for PID %d\n", reqPLeft, pid);
            reqPLeft--;
        }
    }
}

bool Scheduler::emptyRequests()
{
    for (int i = 0; i <= numHosts; i++)
        if (requests[i].frames && requests[i].pid != EMPTY_PID)
            return false;

    return true;
}

void Scheduler::clearRequests(int CS, int AS)
{
    numFrames = 0;

    reqPLeft = numHosts / 2;
    reqPRight = reqPLeft + 1;

    maxFrames = CS - AS;

    for (int i = 0; i <= numHosts; i++)
    {
        requests[i].frames = 0;
        requests[i].sfr = 0;
        requests[i].pid = EMPTY_PID;
    }
}

void Scheduler::clearAllocations()
{
    for (int i = 0; i < MAX_ALLOCATIONS; i++)
    {
        allocations[i].frames = 0;
        allocations[i].pid = EMPTY_PID;
    }
}

/* return the sum of allocated frames */
int Scheduler::getNeededDataFrames()
{
    int frames = 0;

    for (int i = 0; i < MAX_ALLOCATIONS; i++)
        if (allocations[i].pid != EMPTY_PID)
            frames += allocations[i].frames;

    return frames;
}

bool Scheduler::allocateItem(int r)
{
    int i, k;

    if (maxFrames > 0)
    {
        k = -1;

        // find if the PID is present in *allocations
        for (i = 0; i < MAX_ALLOCATIONS; i++)
        {
            if (EMPTY_PID != requests[r].pid && requests[r].pid == allocations[i].pid)
            {
                k = i;
                break;
            }
        }

        if (k >= 0)
        {
            requests[r].frames--;
            maxFrames--;
            allocations[k].frames++;
            return true;   // allocated 1 frame to existing PID
        }

        k = -1;

        //  find an empty slot
        for (i = 0; i < MAX_ALLOCATIONS; i++)
        {
            if (EMPTY_PID == allocations[i].pid)
            {
                k = i;
                break;
            }
        }

        if (k >= 0)
        {
            requests[r].frames--;
            maxFrames--;
            allocations[k].frames++;
            allocations[k].pid = requests[r].pid;
            return true;   // allocated 1 frame to new PID
        }
    }

    return false;   // failed to allocate
}

void Scheduler::allocate()
{
    int i;
    bool running = 1, aborting = 0;

    // Count the number of requested frames
    numReqFrames = 0;
    for (i = 0; i <= numHosts; i++)
        if (requests[i].pid != EMPTY_PID)
            numReqFrames += requests[i].frames;

    while (maxFrames > 0 && running && !aborting)
    {
        // run an allocation round
        for (i = 0; i <= numHosts; i++)
        {
            if (0 < requests[i].frames)
            {
                if (false == allocateItem(i))
                {
                    running = 0;
                    if (maxFrames <= 0)
                        aborting = 1;     // will not proceed anyway!
                    break;
                }
            }
        } //end single allocation round (by 1 frame)

        if (!aborting && maxFrames > 0)
        {
            running = 0;
            for (i = 0; i <= numHosts; i++)
            {
                if (requests[i].frames > 0)
                {
                    running = 1;   // need another round
                    break;
                }
            }
        }

    } //end_while

    numAlcFrames = 0;
    // Count the number of allocated frames
    for (i = 0; i < MAX_ALLOCATIONS; i++)
    {
        if (allocations[i].pid != EMPTY_PID)
        {
            if (allocations[i].frames > requests[i].sfr && requests[i].sfr)
            {
                numPGBK[i] = allocations[i].frames / requests[i].sfr +
                        (allocations[i].frames % requests[i].sfr ? 1 : 0);

                if (maxPGBK < numPGBK[i])
                    numPGBK[i] = maxPGBK;
            }

            numAlcFrames += allocations[i].frames;
        }
    }

}

int Scheduler::getNumOfAllocated()
{
    int k = 0;

    for (int i = 0; i < MAX_ALLOCATIONS; i++)
    {
        if (allocations[i].pid == EMPTY_PID)
        {
            k = i;
            break;
        }
    }

    return k;
}

int Scheduler::getAllocatedPID(int id)
{
    return allocations[id].pid;
}

int Scheduler::getAllocatedFrames(int id)
{
    return allocations[id].frames;
}

int Scheduler::getNumOfAllocatedFrames()
{
    return numAlcFrames;
}

int Scheduler::getNumOfRequestedFrames()
{
    return numReqFrames;
}

int Scheduler::getPGBKCnt(int pid)
{
    return numPGBK[pid];
}

} /* namespace pyxis */
