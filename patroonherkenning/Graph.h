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

template <typename T>
void Graph<T>::addEdge(int source, int destination, const T & edgeVal){
    AdjListNode<T>* follower;
    if(list[source].firstAdjNode){ //there is already a dest node in the adj list
        follower = list[source].firstAdjNode;
        while(follower->next){ //move to the last node in the adj list
            follower = follower->next;
        } //post: there is no follower->next
        AdjListNode<T>* newNode = new AdjListNode<T>;
        newNode->edgeVal = edgeVal;
        newNode->destination = destination;
        newNode->next = nullptr;
        follower->next = newNode;
    }else{ //the source node has no outgoing edges yet
        AdjListNode<T>* newNode = new AdjListNode<T>;
        newNode->edgeVal = edgeVal;
        newNode->destination = destination;
        newNode->next = nullptr;
        list[source].firstAdjNode = newNode;
    }
    if(source > destination){
        if(source > lastGraphNode){
            lastGraphNode = source;
        }
    } else if(destination > lastGraphNode){
        lastGraphNode = destination;
    }
}

template <typename T>
AdjListNode<T>* Graph<T>::findEdge(int source, int destination, const T & edgeVal, AdjListNode<T>*& prevNode){
    if(list[source].firstAdjNode){
        AdjListNode<T>* toFind = list[source].firstAdjNode;
        prevNode = nullptr;
        while(toFind->next && (toFind->destination != destination || toFind->edgeVal != edgeVal)){ //there is a next adjnode and we are not there yet
            prevNode = toFind; //points at the previously seen adjnode
            toFind = toFind->next;
        }
        if(toFind->destination == destination && toFind->edgeVal == edgeVal){ //we have found our edge
            return toFind;
        }
    }
    //edge was not found
    std::cout << "Edge not found: ("<<source<<","<<destination<<")\n";
    return nullptr;
}

template <typename T>
bool Graph<T>::removeEdge(int source, int destination,const T & edgeVal){
    AdjListNode<T>* prevNode;
    AdjListNode<T>* toRemove = findEdge(source, destination, edgeVal, prevNode);
    if(toRemove){ //the edge exists
        if(prevNode){ //it is not the first adjnode
            prevNode->next = toRemove->next;
        } else {
            list[source].firstAdjNode = toRemove->next;
        }
        delete toRemove;
        return true;
    }else{
        return false;
    }
}

template <typename T>
void Graph<T>::print(std::ostream & out){
    for(int i=0; i<=lastGraphNode; i++){
        out<<i;
        AdjListNode<T>* follower = list[i].firstAdjNode;
        while(follower){
            T edg = follower->edgeVal;
            int dest = follower->destination;
            out << " -"<<edg<<"-> " << dest;
            follower = follower->next;
        }
        out << "\n";
    }
}

#endif //GRAPH_H
