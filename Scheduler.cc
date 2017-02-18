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

namespace pyxis {

Scheduler::Scheduler(int hosts)
{
    numHosts = hosts;
    numFrames = 0;
}

Scheduler::~Scheduler()
{
    //empty
}

void Scheduler::addDataRequest(int pid, int frames)
{
    req_t r;

    r.pid = pid;
    r.frames = frames;

    numFrames += r.frames;

    requests.push_back(r);
}

void Scheduler::clearDataRequests()
{
    numFrames = 0;

    while (!requests.empty())
        requests.pop_back();
}

int Scheduler::getNeededDataFrames()
{
    //TODO: should change to allocated data frames
    return numFrames;
}

} /* namespace pyxis */
