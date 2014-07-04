#pragma once
#include "process.h"

namespace scheduler
{

class arrival_queue
{
public:
  arrival_queue(process* proc,size_t n);
  bool empty() const;
  void get(uint64_t time,run_list& list);
private:
  run_list m_queue;
};

}

