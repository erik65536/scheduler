class scheduler
{
public:
  scheduler(uint64_t quantum,file_output& output,std::list<process>& procs);
  void run();
private:
  arrival_queue m_arrival;
  boost_queue m_boost;
  run_queue m_run;
  running m_running;
  file_output& m_output;
};

