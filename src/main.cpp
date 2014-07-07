#include "utility.h"
#include "file_parser.h"
#include "scheduler.h"
#include <unordered_set>
#include <vector>
#include <iostream>

int main(int narg,char** arg)
{
  if(narg != 3)
  {
    std::cout << "scheduler <quanum> <process_file>" << std::endl;
    return -1;
  }

  uint64_t quantum;
  scheduler::string_to_uint64(arg[1],quantum);

  std::vector<scheduler::process> processes;
  try
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
      processes.emplace_back(pid,burst,arrival,priority);
      //std::cout << pid << " " << burst << " " << arrival << " " << priority << std::endl;
    }
  }
  catch(std::logic_error& e)
  {
    std::cout << e.what() << std::endl;
    return -1;
  }

  {
    scheduler::scheduler s(quantum,processes);
    s.run();
  }

  return 0;
}

