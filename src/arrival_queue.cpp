#include "arrival_queue.h"

namespace scheduler
{

arrival_queue::arrival_queue(std::vector<process>& procs)
:m_queue(procs.begin(),procs.end())
{
  m_queue.sort(&process::less_than_arrival_pid);
}

bool arrival_queue::empty() const
{
  return m_queue.empty();
}

void arrival_queue::get(uint64_t time,run_list& list)
{
  auto first = m_queue.begin();
  auto last = first;
  while(last != m_queue.end())
  {
    if(last->arrival() != time)
      break;
    ++last;
  }
  list.splice(list.end(),m_queue,first,last);
}

}
