#include "arrival_queue.h"

namespace scheduler
{

arrival_queue::arrival_queue(std::vector<process>& procs)
:m_queue(procs.begin(),procs.end())
{
  //m_queue.sort(&process::less_than_arrival_pid);
}

bool arrival_queue::empty() const
{
  return m_queue.empty();
}

void arrival_queue::get(uint64_t time,run_list& list)
{
  auto it = m_queue.begin();
  auto end = m_queue.end();
  while(it != end)
  {
    if(it->arrival() != time)
      return;
    process& proc = *it;
    it = m_queue.erase(it);
    list.push_back(proc);
  }
}

}
