#pragma once
#include "process.h"

namespace scheduler
{

class arrival_queue
{
public:
  arrival_queue(std::vector<process>& procs);
  bool empty() const;
  void get(uint64_t time,run_list& list);
private:
  run_list m_queue;
};

}

