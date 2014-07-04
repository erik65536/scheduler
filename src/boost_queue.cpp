#include "boost_queue.h"

namespace scheduler
{

void boost_queue::get(uint64_t time,boost_list& list)
{
  auto start = m_queue.begin();
  auto end = start;
  while(end != m_queue.end())
  {
    if(end->boost() != time)
      break;
    ++end;
  }
  list.splice(list.end(),m_queue,start,end);
}

void boost_queue::insert(uint64_t time,run_list& list)
{
  time = time + BOOST_TIME;
  for(process& proc : list)
  {
    if(proc.priority() >= BOOST_MAX_PRIORITY)
      continue;
    proc.boost() = time;
    m_queue.push_back(proc);
  }
}

void boost_queue::erase(process& proc)
{
  m_queue.erase(m_queue.iterator_to(proc));
}

}


