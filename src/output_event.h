#pragma once
#include <fstream>
#include <cstdint>

namespace scheduler
{

class output_event
{
public:
  output_event(const std::string& file_name);
  ~output_event();
  void event(uint32_t pid,uint64_t start,uint64_t stop,uint8_t priority);
private:
  std::ofstream m_file;
};

}
