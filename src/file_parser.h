#pragma once
#include <fstream>

namespace scheduler
{

class file_parser
{
public:
  file_parser(const char* file_name);
  bool line(uint64_t& pid,uint64_t& burst,uint64_t& arrival,uint64_t& priority);
private:
  bool get_line(uint64_t& pid,uint64_t& burst,uint64_t& arrival,uint64_t& priority);
private:
  std::ifstream m_file;
}; 

}
