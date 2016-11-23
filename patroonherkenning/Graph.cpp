#include "Graph.h"

template <typename T>
Graph<T>::Graph(int numNodes){
    this->numNodes = numNodes;
}

template <typename T>
void Graph<T>::addEdge(int source, int destination, T edgeVal){
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
}

template <typename T>
bool Graph<T>::removeEdge(int source, int destination, T& edgeVal){
    if(list[source].firstAdjNode){
        AdjListNode<T>* toRemove = list[source].firstAdjNode;
        AdjListNode<T>* prevNode = nullptr;
        while(toRemove->next && toRemove->destination != destination){ //there is a next adjnode and we are not there yet
            prevNode = toRemove; //points at the previously seen adjnode
            toRemove = toRemove->next;
        }
        if(toRemove->destination == destination){ //we have found our edge to remove
            if(prevNode){ //this is not the first adjnode
                prevNode->next = toRemove->next;
            }else{
                list[source].firstAdjNode = toRemove->next;
            }
            edgeVal = toRemove->edgeVal;
            delete toRemove;
            return true; //success
        }
    }
    //edge was not found
    std::cerr << "Removing edge failed: ("<<source<<","<<destination<<") not found\n";
    return false;
}

template <typename T>
void Graph<T>::printGraph(){
    for(int i=0; i<numNodes; i++){
        std::cout<<i;
        AdjListNode<T>* follower = list[i].firstAdjNode;
        while(follower){
            T edg = follower->edgeVal;
            int dest = follower->destination;
            std::cout << " -"<<edg<<"-> " << dest;
            follower = follower->next;
        }
        std::cout << "\n";
    }
}
