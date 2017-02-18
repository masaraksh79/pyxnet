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

#include <vector>

namespace pyxis {

typedef struct
{
    int pid;
    int frames;
}
req_t;

class Scheduler {
public:
    Scheduler(int hosts);
    virtual ~Scheduler();
    void addDataRequest(int pid, int frames);
    void clearDataRequests();
    int getNeededDataFrames();
private:
    int numHosts;
    int numFrames;      // number of frames requested from start of AR
    std::vector<req_t> requests;
};

} /* namespace pyxis */

#endif /* SCHEDULER_H_ */
