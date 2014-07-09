#pragma once
#include "process.h"
#include "output_event.h"

namespace scheduler
{

class running
{
public:
  running(output_event* out,uint64_t quantum);
  bool empty() const;
  void get(uint64_t time,run_list& list);
  void run(uint64_t time,process* proc);
private:
  output_event* m_out;
  const uint64_t m_quantum;
  process* m_proc;
  uint64_t m_start;
  uint64_t m_stop;
};

}
