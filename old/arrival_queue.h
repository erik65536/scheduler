#pramga once
#include "process.h"
#include <list>

class arrival_queue
{
public:
  //construct with all processes in list
  arrival_queue(std::list<process>& procs);
  //is queue empty
  bool empty() const;
  //remove from queue and add to list if arrival time == time
  //doesn't add anything if queue is empty
  void get(uint64_t time,std::list<process*>& list);
private:
  std::list<process*> m_queue;
};

