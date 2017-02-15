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

#ifndef JOINLEAVE_H_
#define JOINLEAVE_H_

#include "pkt_m.h"

namespace pyxis {

#define EMPTY_PID   0
#define PID_PB      1
#define PID_PR_MIN  2
#define PID_PR_MAX  252 // maximum is 251 + 1
#define PID_BCAST   255

// Can respond with join allocations at a time (may become dynamic...)
#define NUM_OF_ALLOCATED    4

typedef enum { PID_IDLE = 0, PID_OFFER, PID_GIVEN } pid_state_t;
typedef struct
{
    pid_state_t state;
    int mac;
}
pid_t;

class JoinLeave {
public:
    JoinLeave();
    JoinLeave(BasePkt* pkt, int hosts);
    virtual ~JoinLeave();
    int allocatePID(int mac);
    void addJointoBCS(BasePkt* pkt, int pid, int mac);
    void clearJoinInBCS(BasePkt* pkt);
private:
    int numHosts;
    pid_t *pidTable;
};

} /* namespace pyxis */

#endif /* JOINLEAVE_H_ */
