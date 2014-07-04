#pragma once
#include "process.h"

namespace scheduler
{

class running
{
public:
  running(uint64_t quantum);
  bool empty() const;
  void get(uint64_t time,run_list& list);
  void run(uint64_t time,process* proc);
private:
  const uint64_t m_quantum;
  process* m_proc;
  uint64_t m_start;
  uint64_t m_stop;
};

}

