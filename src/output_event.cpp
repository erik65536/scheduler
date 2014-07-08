#include "output_event.h"
#include <stdexcept>

namespace scheduler
{

output_event::output_event(const char* file_name)
:m_file(file_name)
{
  if(!m_file)
    throw std::logic_error(std::string("Unable to open ").append(file_name).append(" for output."));
  m_file << "var g_event=[";
}

output_event::~output_event()
{
  m_file << "];";
}

void output_event::event(uint32_t pid,uint64_t start,uint64_t stop,uint8_t priority)
{
  m_file << "["
         << start << ","
         << stop << ","
         << pid << ","
         << static_cast<uint32_t>(priority) << "],";
}

}
