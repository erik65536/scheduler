#pragma once
#include "process.h"
#include <fstream>
#include <vector>

namespace scheduler
{

class output_process
{
public:
  output_process(const std::string& file_name);
  void output(std::vector<process>& procs,double avg_turn,double avg_wait);
private:
  std::ofstream m_file;
};

}
