class process
{
public:
  process(const process&) = delete;
  const process& operator=(const process&) = delete;
  process(uint32_t pid,uint64_t burst,uint64_t arrival,uint8_t priority);
  //pid
  uint32_t pid() const;
  //burst
  uint64_t burst() const;
  //remaining burst
  uint64_t remaining() const;
  uint64_t& remaining();
  //arrival time
  uint64_t arrival() const;
  //terminate time
  uint64_t terminate();
  uint64_t& terminate();
  //base priority
  uint8_t base_priority() const;
  //current priority
  uint8_t priority() const;
  uint8_t& priority();
  //boost exiration time
  uint64_t boost() const;
  uint64_t& boost();
  //iterator to boost_queue
  const std::list<process*>::iterator& boost_it() const;
  std::list<process*>::iterator& boost()_it;
  //iterator to run queue
  const std::list<process*>::iterator& run_it() const;
  std::list<process*>::iterator& run()_it;
  //compare for sorting
  static bool less_than_pid(const process& p1,const process& p2);
  static bool less_than_pid_ptr(const process* p1,const process* p2);
  static bool less_than_priority_pid(const process& p1,const process& p2);
  static bool less_than_priority_pid_ptr(const process* p1,const process* p2);
  static bool less_than_arrival_priority_pid(const process& p1,const process& p2);
  static bool less_than_arrival_priority_pid_ptr(const process* p1,const process* p2);
private:
  const uint64_t m_burst;
  uint64_t m_remaining;
  const uint64_t m_arrival;
  uint64_t m_terminate;
  uint64_t m_boost;
  const uint32_t m_pid;
  const uint8_t m_base_priority;
  uint8_t m_priority;
  std::list<process*>::iterator m_boost_it;
  std::list<process*>::iterator m_run_it;
};

