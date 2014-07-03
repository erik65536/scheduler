class file_parser
{
public:
  //open file and read until first line of processes
  //throw std::logic_error if problems opening file
  file_parser(const std::string& file_name);
  //read one line of file and parse
  //doesn't check if values are in range
  //return false if end of file or error
  bool line(uint64_t& pid,uint64_t& burst,uint64_t& arrival,uint64_t& priority);
private:
  std::ifstream m_file;
};

