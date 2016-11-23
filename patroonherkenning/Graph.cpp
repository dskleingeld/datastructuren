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
AdjListNode<T>* Graph<T>::findEdge(int source, int destination, AdjListNode<T>*& prevNode){
    if(list[source].firstAdjNode){
        AdjListNode<T>* toFind = list[source].firstAdjNode;
        prevNode = nullptr;
        while(toFind->next && toFind->destination != destination){ //there is a next adjnode and we are not there yet
            prevNode = toFind; //points at the previously seen adjnode
            toFind = toFind->next;
        }
        if(toFind->destination == destination){ //we have found our edge
            return toFind;
        }
    }
    //edge was not found
    std::cout << "Edge not found: ("<<source<<","<<destination<<")\n";
    return nullptr;
}

template <typename T>
bool Graph<T>::removeEdge(int source, int destination, T& edgeVal){
    AdjListNode<T>* prevNode;
    AdjListNode<T>* toRemove = findEdge(source, destination, prevNode);
    if(toRemove){ //the edge exists
        if(prevNode){ //it is not the first adjnode
            //std::cout << prevNode << " " << prevNode->next << "\n";
            prevNode->next = toRemove->next;
        } else {
            list[source].firstAdjNode = toRemove->next;
        }
        edgeVal = toRemove->edgeVal;
        delete toRemove;
        return true;
    }else{
        return false;
    }
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

int main(){
    Graph<char> graafje(5);
    graafje.addEdge(1, 2, 'a');
    graafje.addEdge(1, 3, 'b');
    graafje.addEdge(1, 4, 'c');
    graafje.addEdge(3, 4, 'd');
    graafje.printGraph();
    
    char removed;
    bool success = graafje.removeEdge(1, 4, removed);
    graafje.printGraph();
    
    success = graafje.removeEdge(3, 4, removed);
    graafje.printGraph();
}
