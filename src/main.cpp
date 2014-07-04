#include "utility.h"
#include "file_parser.h"
#include "scheduler.h"
#include <unordered_set>
//#include <iostream>

int main(int narg,char** arg)
{
  if(narg != 3)
    return -1;
  uint64_t quantum;
  scheduler::string_to_uint64(arg[1],quantum);

  uint32_t count = 0;
  {
    std::unordered_set<uint32_t> pids;
    scheduler::file_parser p(arg[2]);
    uint64_t pid;
    uint64_t burst;
    uint64_t arrival;
    uint64_t priority;
    while(p.line(pid,burst,arrival,priority))
    {
      if(burst == 0)
        continue;
      if(priority >= 100)
        continue;
      if(pids.find(pid) != pids.end())
        continue;
      pids.insert(pid);
      ++count;
      //std::cout << pid << " " << burst << " " << arrival << " " << priority << std::endl;
    }
  }
  scheduler::process* proc = static_cast<scheduler::process*>(malloc(sizeof(scheduler::process)*count));
  uint32_t i = 0;
  {
    std::unordered_set<uint32_t> pids;
    scheduler::file_parser p(arg[2]);
    uint64_t pid;
    uint64_t burst;
    uint64_t arrival;
    uint64_t priority;
    while(p.line(pid,burst,arrival,priority))
    {
      if(burst == 0)
        continue;
      if(priority >= 100)
        continue;
      if(pids.find(pid) != pids.end())
        continue;
      pids.insert(pid);
      new (proc+i)scheduler::process(pid,burst,arrival,priority);
      ++i;
    }
  }
  {
    scheduler::scheduler s(quantum,proc,count);
    s.run();
  }
  return 0;
}

