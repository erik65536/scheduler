#include "scheduler.h"

namespace scheduler
{

scheduler::scheduler(uint64_t quantum,process* procs,size_t n)
  :m_arrival(procs,n),
   m_running(quantum)
{}

void scheduler::run()
{
  uint64_t time = 0;
  run_list add_list;
  boost_list boost;
  while(!m_arrival.empty() || !m_run.empty() || !m_running.empty())
  {
    m_boost.get(time,boost);
    m_run.erase_and_boost(boost,add_list);
    boost.clear();
    m_arrival.get(time,add_list);
    m_running.get(time,add_list);
    add_list.sort();
    m_run.insert(add_list);
    if(m_running.empty())
      m_running.run(time,m_run.top());
    ++time;
  }
}

}

