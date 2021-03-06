#include "file_parser.h"
#include "utility.h"
#include <stdexcept>
#include <array>

namespace scheduler
{

file_parser::file_parser(const std::string& file_name)
:m_file(file_name.c_str())
{
  if(!m_file)
    throw std::logic_error("Unable to open input file "+file_name+".");
}

bool file_parser::line(uint64_t& pid,uint64_t& burst,uint64_t& arrival,uint64_t& priority)
{
  while(!get_line(pid,burst,arrival,priority))
  {
    if(!m_file)
      return false;
  }
  return true;
}

bool file_parser::get_line(uint64_t& pid,uint64_t& burst,uint64_t& arrival,uint64_t& priority)
{
  static std::array<std::string,NCOL> cols;
  cols[0].clear();
  cols[1].clear();
  cols[2].clear();
  cols[3].clear();

  uint32_t col = 0;
  char ch;
  while(true)
  {
    ch = m_file.get();
    if(!m_file)
      break;
    switch(ch)
    {
    case '\r':
    case '\n':
      break;
    case ' ':
    case '\t':
      if(col < NCOL && !cols[col].empty())
        ++col;
      continue;
    default:
      if(col < NCOL)
        cols[col].push_back(ch);
      continue;
    }
    break;
  }
  if(col < NCOL && !cols[col].empty())
    ++col;
  if(col < NCOL)
    return false;
  if(!string_to_uint64(cols[0],pid))
    return false;
  if(!string_to_uint64(cols[1],burst))
    return false;
  if(!string_to_uint64(cols[2],arrival))
    return false;
  if(!string_to_uint64(cols[3],priority))
    return false;
  return true;
}

}
