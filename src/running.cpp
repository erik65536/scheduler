#include "running.h"

namespace scheduler
{

running::running(uint64_t quantum)
  :m_quantum{quantum},
   m_proc{nullptr}
{}

bool running::empty() const
{
  return m_proc == nullptr;
}

void running::get(uint64_t time,run_list& list)
{
  if(m_proc == nullptr)
    return;
  if(time != m_stop)
    return;
  if(m_proc->remaining() != 0)
    list.push_back(*m_proc);
  m_proc = nullptr;
}

void running::run(uint64_t time,process* proc)
{
  if(proc == nullptr)
    return;
  m_proc = proc;
  m_start = time;
  uint64_t run = std::min(m_quantum,proc->remaining());
  proc->remaining() -= run;
  proc->priority() -= std::min(static_cast<uint8_t>(proc->priority()-proc->base_priority()),static_cast<uint8_t>(std::min(run,static_cast<uint64_t>(50))));
  m_stop = time + run;
  if(proc->remaining() == 0)
    proc->terminate() = m_stop;
}

}

