CXX = g++
CXXFLAGS= -Wall -pedantic -std=c++14 -g
#add the flag '-DDEBUG' to enable debug prints

#these 3 lines allow 'make debug' to have debug prints and 'make' not
all: regex
debug: CXXFLAGS += -DDEBUG
debug: regex

objects = main.o Boom.o Graph.o Automaton.o

regex: $(objects)
	$(CXX) $(CXXFLAGS) -o regex main.o Boom.o

main.o: main.cpp Boom.h 
	$(CXX) $(CXXFLAGS) -c main.cpp
Boom.o: Boom.cpp Boom.h
	$(CXX) $(CXXFLAGS) -c Boom.cpp
Automaton.o: Automaton.cpp Automaton.h Graph.h
	$(CXX) $(CXXFLAGS) -c Automaton.cpp
Graph.o: Graph.cpp Graph.h Boom.h
	$(CXX) $(CXXFLAGS) -c Graph.cpp

.PHONY : clean
clean:
	rm regex $(objects)
