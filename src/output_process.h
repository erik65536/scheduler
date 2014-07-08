#pragma once
#include "process.h"
#include <fstream>
#include <vector>

namespace scheduler
{

class output_process
{
public:
  output_process(const char* file_name);
  void output(std::vector<process>& procs);
private:
  std::ofstream m_file;
};

}
