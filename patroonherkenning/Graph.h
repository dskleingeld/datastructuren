#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdlib>
#include <string>

const int maxNodes = 100;

struct AdjListNode{
    char edgeVal;
    int destination;
    AdjListNode* next = nullptr;
};

struct GraphNode{
    AdjListNode* firstAdjNode = nullptr;
};

class Graph{
    protected:
        GraphNode list[maxNodes];
        int numNodes;
    public:
        Graph(int numNodes); //constructor
        
        void addEdge(int source, int destination, char edgeVal);
        void printGraph();
};

#endif //GRAPH_H
