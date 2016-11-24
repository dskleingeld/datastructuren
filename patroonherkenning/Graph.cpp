/**
* Graph<T>: beschrijving van klasse/programma
* @author Eva van Houten (s1478621)
* @author David Kleingeld (s1432982)
* @file Graph.cpp
* @date datum laatste wijziging
**/

#include "Graph.h"

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
        if(toFind->destination == destination && toFind->edgeVal = edgeVal){ //we have found our edge
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
