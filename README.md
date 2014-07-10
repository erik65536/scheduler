scheduler
=========

**TODO**
* output stats to console
* correctness checking
* bug hunting
* optimize
* improve readability

**file_parser:** Memory maps the file for fast access limited only by virtual memory.
* **file_parser(const char* file_name)** Memory map file. May throw exceptions.
* **bool line(uint64_t& pid,uint64_t& burst,uint64_t& arrival,uint64_t& priority)** Read next valid line or return false if end of file.

**process** Information about process. Uses an two intrusive linked lists for faster and simpler code.
* **burst** Total time in CPU.
* **remaining** Time left in CPU.
* **arrival** Arrival time.
* **terminate** Termine time.
* **pid** Unique ID.
* **base_priority** Starting priority.
* **piority** Current priority. May not be less than starting priority.
* Waiting Time = terminate-arrival-burst
* Turnaround Time = terminate-arrival

**arrival_queue** Holds processes ordered first by arrival time then pid. The head of the queue always holds the most recent arrival times.
* **arrival_queue(process* proc,size_t n)** Add processes to list and sort.
* **bool empty() const** If queue is empty.
* **void get(uint64_t time,run_list& list)** Splice processes that arrive at time from this queue to list.

**boost_queue** Holds processes ordered first by boost time then pid. The head of the queue always holds the most recent boost times.
* **void get(uint64_t time,boost_list& list)** Splice processes that are boosted at time from this queue to list.
* **void insert(uint64_t time,run_list& list)** Add processes from list to boost queue if they are eligable to be boosted and set boost time.
* **void erase(process& proc)** Erase process from queue. This process is about to run.

**run_queue** Contains one queue for each priority (an array of queues) and a set of non-empty priorities.
* **bool empty() const** If queue is empty.
* **void insert(run_list& list)** Splice processes into respective priority queues. List must be sorted by pid before calling this function. Remember to maintain set.
* **erase_and_boost(boost_list& boost,run_list& run)** Remove boost processes from respective queues, boost processes, then add to run list. Remember to maintain set.
* **process* top()** Remove the head of the highest priority queue or return nullptr if all queues are empty. Remember to maintain set.

**running** Hold running process.
* **running(uint64_t quantum)** Initialize
* **bool empty() const)** Is process running.
* **void get(uint64_t time,run_list& list)** Add process to list if quantum has expired unless it has terminated.
* **void run(uint64_t time,process* proc)** Start running process at proc. Update remaining time, piority, and terminate time.

**scheduler** Tie together queues.
* **scheduler(uint64_t quantum,process* proc,size_t n)** Initialize
* **void run()** Run simulation.
* Runs each tick until arrival, run, and running queues are empty.
  1. Get boosts.
  2. Remove boosts from run queue, upgrade priority, and copy to add list.
  3. Copy arrivals to add list.
  4. Copy running to add list.
  5. Sort add list. (Could be optimized by merge sorting lists instead)
  6. Copy add list to run queue.
  7. If no process running, remove highest from run and boost queues, then run.

**main**
* Load file and pass data to scheduler. Allocate processes in a memory mapped file so program is limited by virtual memory not physical memory.
* Run scheduler.
* Output statistics.
