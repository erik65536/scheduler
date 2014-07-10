#include "output_process.h"
#include <stdexcept>

namespace scheduler
{

output_process::output_process(const std::string& file_name)
:m_file(file_name.c_str(),std::ios_base::trunc)
{
  if(!m_file)
    throw std::logic_error("Unable to open "+file_name+" for writing.");
}

void output_process::output(std::vector<process>& procs,double avg_turn,double avg_wait)
{
  m_file << "var g_process={stats:{"
         << "total:" << procs.size() << ","
         << "turnaround:" << avg_turn << ","
         << "wait:" << avg_wait << "},process:{";
  for(process& proc : procs)
  {
    uint64_t turn = proc.terminate()-proc.arrival();
    m_file << proc.pid() << ":["
           << proc.arrival() << ","
           << proc.terminate() << ","
           << proc.burst() << ","
           << static_cast<uint32_t>(proc.base_priority()) << ","
           << turn << ","
           << turn-proc.burst() << "],";
  }
  m_file << "}};";
}

}
