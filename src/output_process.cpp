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

void output_process::output(std::vector<process>& procs)
{
  uint64_t total_turn = 0;
  uint64_t total_wait = 0;
  uint64_t turn;
  for(process& proc : procs)
  {
    turn = proc.terminate()-proc.arrival();
    total_turn += turn;
    total_wait += turn-proc.burst();
  }
  m_file << "stats:{"
         << "total:" << procs.size() << ","
         << "turnaround:" << static_cast<double>(total_turn)/static_cast<double>(procs.size()) << ","
         << "wait:" << static_cast<double>(total_wait)/static_cast<double>(procs.size()) << "},process:{";

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
