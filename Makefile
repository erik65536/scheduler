CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCES=src/main.cpp src/file_parser.cpp src/utility.cpp src/process.cpp src/arrival_queue.cpp
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
