#include "arrival_queue.h"

namespace scheduler
{

arrival_queue::arrival_queue(process* proc,size_t n)
{
  for(size_t i=0; i<n; ++i)
    m_list.push_back(*proc);
}

bool arrival_queue::empty() const
{
  return m_list.empty();
}

void arrival_queue::get(uint64_t time,run_list& list)
{
  auto start = m_list.begin();
  auto end = start;
  while(end != m_list.end())
  {
    if(end->arrival() != time)
      break;
  }
  list.splice(list.end(),m_list,start,end);
}

}

