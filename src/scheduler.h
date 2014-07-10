#pragma once
#include "arrival_queue.h"
#include "boost_queue.h"
#include "running.h"
#include "run_queue.h"
#include <chrono>

namespace scheduler
{

class scheduler
{
private:
  static const std::chrono::milliseconds PRINT_INTERVAL;
public:
  scheduler(output_event* out,uint64_t quantum,std::vector<process>& procs);
  void run(size_t nprocess);
private:
  arrival_queue m_arrival;
  boost_queue m_boost;
  run_queue m_run;
  running m_running;
};

}
