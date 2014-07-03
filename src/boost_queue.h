class boost_queue
{
public:
  //remove from queue and add to list if boost time == time
  //doesn't add anything if queue is empty
  void get(uint64_t time,std::list<process*>& list);
  //insert to queue if priority < 49 and set boost time
  void insert(uint64_t time,std::list<process*>& list);
  //erase single process from queue
  void erase(process* proc);
private:
  std::list<uint64_t> m_queue;
};

