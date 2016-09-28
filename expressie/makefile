CXX = g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic

expressie: main.o Boom.o
	$(CXX) $(CXXFLAGS) -o Boom.o main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
Boom.o: Boom.cpp
	$(CXX) $(CXXFLAGS) -c Boom.cpp	
clean:
	rm Boom.o main.o

#http://www.gnu.org/software/make/manual/make.html#Introduction
