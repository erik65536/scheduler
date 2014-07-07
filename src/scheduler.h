#pragma once
#include "arrival_queue.h"
#include "boost_queue.h"
#include "running.h"
#include "run_queue.h"

namespace scheduler
{

class scheduler
{
public:
  scheduler(uint64_t quantum,std::vector<process>& procs);
  void run();
private:
  arrival_queue m_arrival;
  boost_queue m_boost;
  run_queue m_run;
  running m_running;
};

}

