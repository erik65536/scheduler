#include "process.h"

namespace scheduler
{

process::process(process&& proc)
:hook_run(proc),
hook_boost(proc),
m_burst{proc.m_burst},
m_remaining{proc.m_remaining},
m_arrival{proc.m_arrival},
m_terminate{proc.m_terminate},
m_boost{proc.m_boost},
m_pid{proc.m_pid},
m_base_priority{proc.m_base_priority},
m_priority{proc.m_priority}
{}

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

}
