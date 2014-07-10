#include "utility.h"
#include "file_parser.h"
#include <unordered_set>
#include <iostream>
#include <boost/algorithm/string.hpp>

namespace scheduler
{

bool string_to_uint64(const std::string& string,uint64_t& value)
{
  const char* ptr = string.c_str();
  char ch;
  if((ch = *(ptr++)) == 0)
    return false;
  if(ch > '9')
    return false;
  if(ch < '0')
    return false;
  value = ch - '0';
  while((ch = *(ptr++)) != 0)
  {
    if(ch > '9')
      return false;
    if(ch < '0')
      return false;
    value = value*10 + (ch - '0');
  }
  return true;
}

size_t process_from_file(const std::string& file_name,std::vector<process>* container)
{
  size_t n = 0;

  file_parser file(file_name);
  std::unordered_set<uint32_t> pids;
  uint64_t pid;
  uint64_t burst;
  uint64_t arrival;
  uint64_t priority;
  while(file.line(pid,burst,arrival,priority))
  {
    if(burst == 0)
      continue;
    if(priority > MAX_PRIORITY)
      continue;
    if(pids.find(static_cast<uint32_t>(pid)) != pids.end())
      continue;
    pids.insert(static_cast<uint32_t>(pid));
    if(container != nullptr)
      container->emplace_back(static_cast<uint32_t>(pid),burst,arrival,static_cast<uint8_t>(priority));
    ++n;
  }
  return n;
}

void print_help()
{
  std::cout << "scheduler -q [quantum] -i [process file] -n|-o" << std::endl
            << "  --help     Print help." << std::endl
            << "   -h" << std::endl
            << "  --quantum  Time quantum." << std::endl
            << "   -q" << std::endl
            << "  --input    Input file." << std::endl
            << "   -i" << std::endl
            << "  --out      Output to files. (default)" << std::endl
            << "   -o" << std::endl
            << "  --noout    Do not output to files." << std::endl
            << "   -n" << std::endl;
}

bool parse_arguments(int narg,char** arg,uint64_t& quantum,std::string& input_file,bool& output)
{
  if(narg == 1)
    return false;

  bool is_quantum = false;
  bool is_input = false;
  bool is_noout = false;
  bool is_out = false;

  output = true;
  for(int i=1; i<narg; ++i)
  {
    if(boost::iequals("-h",arg[i]) || boost::iequals("--h",arg[i]) ||
       boost::iequals("-help",arg[i]) || boost::iequals("--help",arg[i]) ||
       boost::iequals("help",arg[i]))
    {
      return false;
    }
    else if(boost::iequals("-q",arg[i]) || boost::iequals("--quantum",arg[i]))
    {
      if(is_quantum)
      {
        std::cout << "Error: Quantum specified multiple times." << std::endl;
        return false;
      }
      if(i+1 >= narg)
      {
        std::cout << "Error: No value specified for quantum." << std::endl;
        return false;
      }
      if(!string_to_uint64(arg[i+1],quantum))
      {
        std::cout << "Error: Quantum is not a positive integer." << std::endl;
        return false;
      }
      if(quantum == 0)
      {
        std::cout << "Error: Quantum is zero." << std::endl;
        return false;
      }
      ++i;
      is_quantum = true;
    }
    else if(boost::iequals("-i",arg[i]) || boost::iequals("--input",arg[i]))
    {
      if(is_input)
      {
        std::cout << "Error: Input file specified multiple times." << std::endl;
        return false;
      }
      if(i+1 >= narg)
      {
        std::cout << "Error: No value specified for input file." << std::endl;
        return false;
      }
      input_file = arg[i+1];
      ++i;
      is_input = true;
    }
    else if(boost::iequals("-o",arg[i]) || boost::iequals("--out",arg[i]))
    {
      if(is_out)
      {
        std::cout << "Error: Output to file specified multipel times." << std::endl;
        return false;
      }
      if(is_noout)
      {
        std::cout << "Error: Output to file conflicts with no output to file." << std::endl;
        return false;
      }
      is_out = true;
    }
    else if(boost::iequals("-n",arg[i]) || boost::iequals("--noout",arg[i]))
    {
      if(is_noout)
      {
        std::cout << "Error: No output to file specified multiple times." << std::endl;
        return false;
      }
      if(is_out)
      {
        std::cout << "Error: No output to file conflicts with output to file." << std::endl;
        return false;
      }
      output = false;
      is_noout = true;
    }
    else
    {
      std::cout << "Error: Unrecognized Option: " << arg[i] << std::endl;
      return false;
    }
  }
  if(!is_quantum)
  {
    std::cout << "Error: No quantum specified." << std::endl;
    return false;
  }
  if(!is_input)
  {
    std::cout << "Error: No input file specified." << std::endl;
    return false;
  }
  return true;
}

}
