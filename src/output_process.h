#pragma once
#include "process.h"
#include <fstream>

namespace scheduler
{

class output_process
{
public:
  output_process(const char* file_name);
  ~output_process();
  void output(std::vector<process>& procs);
private:
  std::ofstream m_file;
};

}
