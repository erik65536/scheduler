#pragma once
#include "process.h"
#include <array>
#include <set>

namespace scheduler
{

class run_queue
{
private:
  static const uint8_t PRIORITY_N = 100;
  static const uint8_t PRIORITY_BOOST[48];
public:
  bool empty() const;
  void insert(run_list& list);
  void erase_and_boost(boost_list& boost,run_list& run);
  process* top();
private:
  std::set<uint8_t> m_nonempty;
  std::array<run_list,PRIORITY_N> m_queue;
};

}

