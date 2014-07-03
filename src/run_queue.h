class run_queue
{
private:
  static const uint8_t PRIORITY_N = 100;
public:
  //is queue empty
  bool empty() const;
  //remove head process from highest queue and return pointer
  //return nullptr if queue is empty
  process* get();
  //insert processes to queue, update priority before calling this function
  void insert(std::list<process*>& procs);
  //erase processes from queue, update priority after calling this function
  void erase(std::list<process*>& procs);
private:
  std::array<std::list<process*>,PRIORITY_N> m_queue;
  std::set<uint8_t> m_nonempty;
};

