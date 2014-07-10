#pragma once
#include "process.h"
#include "output_event.h"
#include <chrono>

namespace scheduler
{

class running
{
private:
  static const std::chrono::milliseconds PRINT_INTERVAL;
public:
  running(output_event* out,uint64_t quantum,size_t nprocess);
  bool empty() const;
  void get(uint64_t time,run_list& list);
  void run(uint64_t time,process* proc);
private:
  output_event* m_out;
  const uint64_t m_quantum;
  process* m_proc;
  uint64_t m_start;
  uint64_t m_stop;
  std::chrono::high_resolution_clock::time_point m_real_time;
  size_t m_nprocess;
  size_t m_terminate;
  double m_dnprocess;
};

}
