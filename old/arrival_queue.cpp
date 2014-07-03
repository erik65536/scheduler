#include "arrival_queue.h"

arrival_queue::arrival_queue(std::list<process>& procs)
{
  for(process& proc : procs)
    m_queue.push_back(&proc);
}

bool arrival_queue::empty() const
{
  return m_qeueue.empty();
}

void arrival_queue::get(uint64_t time,std::list<process*>& list)
{
  auto start = m_queue.begin();
  auto end = start;
  while(end != m_queue.end())
  {
    if((*end)->arrival() != time)
      break;
    ++end;
  }
  list.splice(list.end(),m_queue,start,end);
}

