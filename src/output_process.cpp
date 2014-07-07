#include "output_process.h"
#include <stdexcept>

namespace scheduler
{

output_process::output_process(const char* file_name)
  :m_file(file_name,std::ios_base::trunc)
{
  if(!m_file)
    throw std::logic_error(std::string("Unable to open ").append(file_name).append(" for writing."));
  m_file << "var g_process={";
}

output_process::~output_process()
{
  m_file << "};";
}
 
void output_process::output(std::vector<process>& procs)
{
  for(process& proc : procs)
  {
    m_file << proc.pid() << ":[" 
           << proc.arrival() << ","
           << proc.terminate() << ","
           << proc.burst() << ","
           << proc.base_priority() << "],";
  }
}

}
