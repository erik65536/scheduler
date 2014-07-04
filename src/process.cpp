#include "process.h"

namespace scheduler
{

process::process(uint32_t pid,uint64_t burst,uint64_t arrival,uint8_t priority)
  :m_burst{burst},
   m_remaining{burst},
   m_arrival{arrival},
   m_terminate{0},
   m_boost{0},
   m_pid{pid},
   m_base_priority{priority},
   m_priority{priority}
{}

uint64_t process::burst() const
{
  return m_burst;
}

uint64_t process::remaining() const
{
  return m_remaining;
}

uint64_t& process::remaining()
{
  return m_remaining;
}

uint64_t process::arrival() const
{
  return m_arrival;
}

uint64_t process::terminate() const
{
  return m_terminate;
}

uint64_t& process::terminate()
{
  return m_terminate;
}

uint64_t process::boost() const
{
  return m_boost;
}

uint64_t& process::boost()
{
  return m_boost;
}

uint32_t process::pid() const
{
  return m_pid;
}

uint8_t process::base_priority() const
{
  return m_base_priority;
}

uint8_t process::priority() const
{
  return m_priority;
}

uint8_t& process::priority()
{
  return m_priority;
}

bool process::operator<(const process& proc) const
{
  return m_pid < proc.m_pid;
}

bool process::less_than_arrival_pid(const process& proc1,const process& proc2)
{
  if(proc1.m_arrival == proc2.m_arrival)
    return proc1.m_pid < proc2.m_pid;
  return proc1.m_arrival < proc2.m_arrival;
}

}

