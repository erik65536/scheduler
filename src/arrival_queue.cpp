#include "arrival_queue.h"

namespace scheduler
{

arrival_queue::arrival_queue(process* proc,size_t n)
{
  for(size_t i=0; i<n; ++i)
    m_queue.push_back(*(proc+i));
  m_queue.sort(&process::less_than_arrival_pid);
}

bool arrival_queue::empty() const
{
  return m_queue.empty();
}

void arrival_queue::get(uint64_t time,run_list& list)
{
  auto start = m_queue.begin();
  auto end = start;
  while(end != m_queue.end())
  {
    if(end->arrival() != time)
      break;
    ++end;
  }
  list.splice(list.end(),m_queue,start,end);
}

}

