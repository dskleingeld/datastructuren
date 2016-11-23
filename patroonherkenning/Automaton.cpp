#include "Graph.h"
#include "Automaton.h"
#include "Boom.h"

Automaton::Automaton(int numNodes) : Graph(numNodes){
    this->numNodes = numNodes;
    this->addEdge(0, 1, '$'); //add a lambda egde between i and f (always 0 and 1)
}
        
void Automaton::addConcat(int start, int end, Leaf* left, Leaf* right){
    
}

void Automaton::addStar(int start, int end, Leaf* left){
    
}

void Automaton::addChoice(int start, int end, Leaf* left, Leaf* right){
    
}

void Automaton::processOperation(Leaf* operationNode){
    switch(operationNode->operand){
        case CONCAT:
            this.addConcat(
}

int main(){
    Automaton floepie(10);
    floepie.printGraph();
    
    return 0;
}
