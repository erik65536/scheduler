#include "run_queue.h"

namespace scheduler
{

const uint8_t run_queue::PRIORITY_BOOST[49] = {10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,49,49,49,49,49,49,49,49,49};

bool run_queue::empty() const
{
  return m_nonempty.empty();
}

void run_queue::insert(run_list& list)
{
  auto it = list.begin();
  auto end = list.end();
  while(it != end)
  {
    process& proc = *it;
    uint8_t priority = proc.priority();
    run_list& queue = m_queue[priority];
    if(queue.empty())
      m_nonempty.insert(priority);
    it = list.erase(it);
    queue.push_back(proc);
  }
}

void run_queue::erase_and_boost(boost_list& boost,run_list& run)
{
  for(process& proc : boost)
  {
    uint8_t priority = proc.priority();
    run_list& queue = m_queue[priority];
    queue.erase(queue.iterator_to(proc));
    if(queue.empty())
      m_nonempty.erase(priority);
    proc.priority() = PRIORITY_BOOST[priority];
    run.push_back(proc);
  }
}

process* run_queue::top()
{
  if(m_nonempty.empty())
    return nullptr;
  uint8_t priority = *m_nonempty.rbegin();
  run_list& queue = m_queue[priority];
  process* proc = &queue.front();
  queue.pop_front();
  if(queue.empty())
    m_nonempty.erase(priority);
  return proc;
}

}
