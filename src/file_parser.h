#pragma once
#include <fstream>
#include <cstdint>

namespace scheduler
{

class file_parser
{
private:
  static const uint32_t NCOL = 4;
public:
  file_parser(const char* file_name);
  bool line(uint64_t& pid,uint64_t& burst,uint64_t& arrival,uint64_t& priority);
private:
  bool get_line(uint64_t& pid,uint64_t& burst,uint64_t& arrival,uint64_t& priority);
private:
  std::ifstream m_file;
};

}
