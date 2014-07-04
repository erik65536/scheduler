#include "file_parser.h"
#include "utility.h"

namespace scheduler
{

file_parser::file_parser(const char* file_name)
  :m_file(file_name,boost::interprocess::read_only),
   m_map(m_file,boost::interprocess::read_only),
   m_cur(static_cast<char*>(m_map.get_address())),
   m_end(static_cast<char*>(m_map.get_address())+m_map.get_size())
{}

bool file_parser::line(uint64_t& pid,uint64_t& burst,uint64_t& arrival,uint64_t& priority)
{
  while(m_cur != m_end)
  {
    if(get_line(pid,burst,arrival,priority))
      return true;
  }
  return false;
}

bool file_parser::get_line(uint64_t& pid,uint64_t& burst,uint64_t& arrival,uint64_t& priority)
{
  static std::array<std::string,4> cols;
  cols[0].clear();
  cols[1].clear();
  cols[2].clear();
  cols[3].clear();
  uint32_t col = 0;
  char ch;
  while(m_cur != m_end)
  {
    ch = *(m_cur++);
    switch(ch)
    {
    case '\r':
    case '\n':
      break;
    case ' ':
    case '\t':
      if(col < 4 && !cols[col].empty())
        ++col;
      continue;
    default:
      if(col < 4)
       cols[col].push_back(ch);
      continue;
    }
    break;
  }
  if(col < 4 && !cols[col].empty())
    ++col;
  if(col >= 4)
  {
    if(!string_to_uint64(cols[0],pid))
      return false;
    if(!string_to_uint64(cols[1],burst))
      return false;
    if(!string_to_uint64(cols[2],arrival))
      return false;
    if(!string_to_uint64(cols[3],priority))
      return false;
  }
  else
    return false;
  return true;
}

}

