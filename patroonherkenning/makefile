CXX = g++
CXXFLAGS= -Wall -pedantic -std=c++14 -g -DDEBUG
#add the flag '-DDEBUG' to enable debug statements

objects = main.o Boom.o

regex: $(objects)
	$(CXX) $(CXXFLAGS) -o regex main.o Boom.o

main.o: main.cpp Boom.h 
	$(CXX) $(CXXFLAGS) -c main.cpp
Boom.o: Boom.cpp Boom.h
	$(CXX) $(CXXFLAGS) -c Boom.cpp


.PHONY : clean
clean:
	rm regex $(objects)
