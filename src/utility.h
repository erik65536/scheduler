#pragma once
#include "process.h"
#include <string>
#include <cstdint>
#include <vector>

namespace scheduler
{

static const uint8_t MAX_PRIORITY = 99;

bool string_to_uint64(const std::string& string,uint64_t& value);
size_t process_from_file(const std::string& file_name,std::vector<process>* container);
void print_help();
bool parse_arguments(int narg,char** arg,uint64_t& quantum,std::string& input_file,bool& output);

};
