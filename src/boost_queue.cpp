#include "boost_queue.h"

namespace scheduler
{

void boost_queue::get(uint64_t time,boost_list& list)
{
  auto first = m_queue.begin();
  auto last = first;
  while(last != m_queue.end())
  {
    if(last->boost() != time)
      break;
    ++last;
  }
  list.splice(list.end(),m_queue,first,last);
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

void boost_queue::erase(process* proc)
{
  if(proc == nullptr)
    return;
  if(!proc->hook_boost::is_linked())
    return;
  m_queue.erase(m_queue.iterator_to(*proc));
}

}
