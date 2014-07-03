#pragma once
#include <boost/intrusive/list.hpp>

namespace scheduler
{

struct tag_run;
struct tag_boost;
typedef boost::intrusive::list_base_hook<boost::intrusive::tag<tag_run>> hook_run;
typedef boost::intrusive::list_base_hook<boost::intrusive::tag<tag_boost>> hook_boost;

class process : public hook_run, public hook_boost
{
public:
  process(const process&) = delete;
  const process& operator=(const process&) = delete;
  process(uint32_t pid,uint64_t burst,uint64_t arrival,uint8_t priority);
  uint64_t burst() const;
  uint64_t remaining() const;
  uint64_t& remaining();
  uint64_t arrival() const;
  uint64_t terminate() const;
  uint64_t& terminate();
  uint64_t boost() const;
  uint64_t& boost();
  uint32_t pid() const;
  uint8_t base_priority() const;
  uint8_t priority() const;
  uint8_t& priority();
private:
  const uint64_t m_burst;
  uint64_t m_remaining;
  const uint64_t m_arrival;
  uint64_t m_terminate;
  uint64_t m_boost;
  const uint32_t m_pid;
  const uint8_t m_base_priority;
  uint8_t m_priority;
};

typedef boost::intrusive::list<process,boost::intrusive::base_hook<hook_run>,boost::intrusive::constant_time_size<false>> run_list;
typedef boost::intrusive::list<process,boost::intrusive::base_hook<hook_boost>,boost::intrusive::constant_time_size<false>> run_boost;

}
