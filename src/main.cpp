#include "utility.h"
#include "output_process.h"
#include "output_event.h"
#include "scheduler.h"
#include <vector>
#include <iostream>

int main(int narg,char** arg)
{
  static const char* FILE_EVENT = "output_event.js";
  static const char* FILE_PROCESS = "output_process.js";

  //parse arguments
  uint64_t quantum;
  std::string input_file;
  bool output;
  if(!scheduler::parse_arguments(narg,arg,quantum,input_file,output))
  {
    scheduler::print_help();
    return -1;
  }

  try
  {
    //load from file
    size_t nprocess = scheduler::process_from_file(input_file,nullptr);
    std::cout << "Found " << nprocess << " valid processes in " << input_file << "." << std::endl;
    std::vector<scheduler::process> processes;
    processes.reserve(nprocess);
    scheduler::process_from_file(input_file,&processes);
    //run scheduler
    {
      if(output)
      {
        scheduler::output_event out(FILE_EVENT);
        scheduler::scheduler s(&out,quantum,processes);
        s.run();
      }
      else
      {
        scheduler::scheduler s(nullptr,quantum,processes);
        s.run();
      }
    }
    //output
    if(output)
    {
      scheduler::output_process out(FILE_PROCESS);
      out.output(processes);
    }
  }
  catch(std::logic_error& e)
  {
    std::cout << "Error: " << e.what() << std::endl;
    return -1;
  }

  return 0;
}

