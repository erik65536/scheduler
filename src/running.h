class running
{
public:
  running(uint64_t quantum);
  //return process if quantum finished or nullptr if no process running
  //also returns start and stop time of quantum for output
  process* get(uint64_t time,uint64_t& start,uint64_t& stop);
  //start running process
  void run(uint64_t time,process* proc);
private:
  const uint64_t m_quantum;
  uint64_t start;
  uint64_t stop;
  process* m_running;
};

