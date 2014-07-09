#include "scheduler.h"

namespace scheduler
{

scheduler::scheduler(output_event* out,uint64_t quantum,std::vector<process>& procs)
:m_arrival(procs),
m_running(out,quantum)
{}

void scheduler::run()
{
  uint64_t time = 0;

  run_list add_list;
  run_list add_list2;
  boost_list boost;
  while(!m_arrival.empty() || !m_run.empty() || !m_running.empty())
  {
    m_boost.get(time,boost);
    m_run.erase_and_boost(boost,add_list);
    boost.clear();

    m_running.get(time,add_list2);
    add_list.merge(add_list2);

    m_arrival.get(time,add_list2);
    add_list.merge(add_list2);

    m_boost.insert(time,add_list);
    m_run.insert(add_list);

    if(m_running.empty())
    {
      process* proc = m_run.top();
      m_boost.erase(proc);
      m_running.run(time,proc);
    }

    ++time;
  }
}

}
