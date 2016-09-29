CXX = g++
CXXFLAGS=-g -Wall -pedantic

expressie: main.o Boom.o
	$(CXX) $(CXXFLAGS) -o expressie Boom.o main.o #"-o expressie" needed
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
Boom.o: Boom.cpp
	$(CXX) $(CXXFLAGS) -c Boom.cpp	
clean:
	rm Boom.o main.o

#http://www.gnu.org/software/make/manual/make.html#Introduction
