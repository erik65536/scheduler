class file_output
{
  //open output json files
  //throw std::logic_error if problems opening files
  file_output(const std::string& file_name);
  //finish writing to files
  ~file_output();
  //add run quantum to json array in file
  void quantum(process* proc,uint64_t start,uint64_t stop);
  //write stats to json array
  void stats(const std::list<process>& procs);
private:
  std::ofstream m_json_quantum;
  std::ofstream m_json_stats;
};

