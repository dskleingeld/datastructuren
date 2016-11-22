#include "Graph.h"

Graph::Graph(int numNodes){
    this->numNodes = numNodes;
}

void Graph::addEdge(int source, int destination, char edgeVal){
    AdjListNode* follower;
    if(list[source].firstAdjNode){ //there is already a dest node in the adj list
        follower = list[source].firstAdjNode;
        while(follower->next){ //move to the last node in the adj list
            follower = follower->next;
        } //post: there is no follower->next
        AdjListNode* newNode = new AdjListNode;
        newNode->edgeVal = edgeVal;
        newNode->destination = destination;
        newNode->next = nullptr;
        follower->next = newNode;
    }else{ //the source node has no outgoing edges yet
        AdjListNode* newNode = new AdjListNode;
        newNode->edgeVal = edgeVal;
        newNode->destination = destination;
        newNode->next = nullptr;
        list[source].firstAdjNode = newNode;
    }
}

void Graph::printGraph(){
    for(int i=0; i<numNodes; i++){
        std::cout<<i;
        AdjListNode* follower = list[i].firstAdjNode;
        while(follower){
            char edg = follower->edgeVal;
            int dest = follower->destination;
            std::cout << " -"<<edg<<"-> " << dest;
            follower = follower->next;
        }
        std::cout << "\n";
    }
}
