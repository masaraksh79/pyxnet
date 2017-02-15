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

#include <JoinLeave.h>

namespace pyxis {

//TODO: implement drop node and replacement of it with another node when lack space
//TODO: manage cycle timeouts per PID to find the oldest

JoinLeave::JoinLeave(BasePkt* pkt, int hosts)
{
    numHosts = hosts;

    pidTable = new pid_t[PID_PR_MAX];

    for (int i = 0; i < PID_PR_MAX; i++)
    {
        pidTable[i].state = PID_IDLE;
        pidTable[i].mac = 0;
    }

    pkt->setMacsArraySize(NUM_OF_ALLOCATED);
    pkt->setPidsArraySize(NUM_OF_ALLOCATED);
}

JoinLeave::~JoinLeave()
{
    delete pidTable;
}

int JoinLeave::allocatePID(int mac)
{
    int i;

    // find if the MAC is present already
    for (i = PID_PR_MAX - 1; i >= PID_PR_MIN; i--)
    {
        if (PID_IDLE < pidTable[i].state && pidTable[i].mac == mac)
            return i;
    }

    // offer a new one
    for (i = PID_PR_MAX - 1; i >= PID_PR_MIN; i--)
    {
        if (PID_IDLE == pidTable[i].state)
        {
            pidTable[i].state = PID_OFFER;
            pidTable[i].mac = mac;
            return i;
        }
    }

    return EMPTY_PID;
}

void JoinLeave::addJointoBCS(BasePkt* pkt, int pid, int mac)
{
    for (int i = 0; i < NUM_OF_ALLOCATED; i++)
    {
        if (EMPTY_PID == pkt->getPids(i))
        {
            pkt->setPids(i, pid);
            pkt->setMacs(i, mac);
            return;
        }
    }
}

void JoinLeave::clearJoinInBCS(BasePkt* pkt)
{
    for (int i = 0; i < NUM_OF_ALLOCATED; i++)
    {
        pkt->setPids(i, EMPTY_PID);
        pkt->setMacs(i, 0);
    }
}


} /* namespace pyxis */
