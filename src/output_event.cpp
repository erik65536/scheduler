#include "output_event.h"
#include <stdexcept>

namespace scheduler
{

output_event::output_event(const std::string& file_name)
:m_file(file_name.c_str())
{
  if(!m_file)
    throw std::logic_error("Unable to open "+file_name+" for writing.");
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
