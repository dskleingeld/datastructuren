#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdlib>
#include <string>

const int maxNodes = 100;

template <typename T>
struct AdjListNode{
    T edgeVal;
    int destination;
    AdjListNode<T>* next = nullptr;
};

template <typename T>
struct GraphNode{
    AdjListNode<T>* firstAdjNode = nullptr;
};

template <typename T>
class Graph{
    protected:
        GraphNode<T> list[maxNodes];
        int numNodes;
    public:
        Graph(int numNodes); //constructor
        
        void addEdge(int source, int destination, T edgeVal);
        bool removeEdge(int source, int destination, T& edgeVal); //removes an edge and returns the edge value
        
        void printGraph();
};

#endif //GRAPH_H
