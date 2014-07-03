#include "file_parser.h"
#include <iostream>

int main(int narg,char** arg)
{
  if(narg != 2)
    return -1;
  scheduler::file_parser p(arg[1]);
  uint64_t pid;
  uint64_t burst;
  uint64_t arrival;
  uint64_t priority;
  while(p.line(pid,burst,arrival,priority))
  {
    std::cout << pid << " " << burst << " " << arrival << " " << priority << std::endl;
  }
  return 0;
}

