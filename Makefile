CC=g++
#CFLAGS=-c -Wall -std=c++11 -O3
#LDFLAGS=-O3
#google-perftools
CFLAGS=-c -Wall -std=c++11 -g -O3
LDFLAGS=-O3 -g -lprofiler
#debug
#CFLAGS=-c -Wall -std=c++11 -g -fno-inline
#LDFLAGS=-g -fno-inline
SOURCES=src/main.cpp src/file_parser.cpp src/utility.cpp src/process.cpp src/arrival_queue.cpp src/boost_queue.cpp src/run_queue.cpp src/running.cpp src/scheduler.cpp src/output_process.cpp src/output_event.cpp
INC=-I.
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=scheduler

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INC) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
