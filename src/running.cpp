#include "running.h"

namespace scheduler
{

running::running(output_event& out,uint64_t quantum)
:m_out(out),
m_quantum{quantum},
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
  m_stop = time + run;
  proc->remaining() -= run;
  if(proc->remaining() == 0)
    proc->terminate() = m_stop;
  m_out.event(proc->pid(),m_start,m_stop,proc->priority());

  uint8_t pri_diff = proc->priority()-proc->base_priority();
  run = std::min(run,static_cast<uint64_t>(255));
  proc->priority() -= std::min(pri_diff,static_cast<uint8_t>(run));
}

}
