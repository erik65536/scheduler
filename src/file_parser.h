#pragma once
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

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
  boost::interprocess::file_mapping m_file;
  boost::interprocess::mapped_region m_map;
  char* m_cur;
  char* m_end;
}; 

}
