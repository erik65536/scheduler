#pragma once
#include "process.h"

namespace scheduler
{

class boost_queue
{
private:
  static const uint64_t BOOST_TIME = 100;
  static const uint8_t BOOST_MAX_PRIORITY = 49;
public:
  void get(uint64_t time,boost_list& list);
  void insert(uint64_t time,run_list& list);
  void erase(process* proc);
private:
  boost_list m_queue;
};

}

