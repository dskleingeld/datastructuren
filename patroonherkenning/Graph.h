/**
* Graph<T>: a directed, weighted graph, with weigths of type T
* @author Eva van Houten (s1478621)
* @author David Kleingeld (s1432982)
* @file Graph.h
* @date datum laatste wijziging
**/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

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
    public:
    /**
    * @function addEdge
    * @abstract add an edge to the graph
    * @param source the beginning of the edge
    * @param destination the end of the edge
    * @param edgeVal the value along the edge
    * @post the edge (source, destination, edgeVal) has been added
    **/
    void addEdge(int source, int destination, const T & edgeVal);
    /**
    * @function removeEdge
    * @abstract remove an edge of the graph if possible
    * @param source the beginning of the edge
    * @param destination the end of the edge
    * @param edgeVal the value along the edge (two edges between the
    * same nodes are allowed)
    * @return a boolean signalling success
    * @post the edge (source, destination, edgeVal) has been removed
    **/
    bool removeEdge(int source, int destination, const T & edgeVal);
    /**
    * @function print
    * @abstract print the Graph as an adjacency list
    * @param out the ostream to send the printing output to
    **/
    void print(std::ostream & out);
    
    protected:
    GraphNode<T> list[maxNodes];
    int lastGraphNode = 0;
    
    AdjListNode<T>* findEdge(int source, int destination, const T & edgeVal, AdjListNode<T>*& prevNode);
    
    
};

#endif //GRAPH_H
