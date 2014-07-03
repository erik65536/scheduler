#include "utility.h"

bool utility::string_to_uint64(const std::string& string,uint64_t& value)
{
  value = 0;
  const char* ptr = string.c_str();
  char ch;
  if((ch = *(ptr++)) == 0)
    return false;
  val = ch - '0';
  while((ch = *(ptr++)) != 0)
  {
    if(ch < '0')
      return false;
    if(ch > '9')
      return false;
    value = value*10 + (ch - '0');
  }
  return true;
}

