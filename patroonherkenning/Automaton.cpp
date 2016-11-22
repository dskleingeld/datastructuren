#include "Graph.h"
#include "Automaton.h"

Automaton::Automaton(int numNodes) : Graph(numNodes){
    this->numNodes = numNodes;
    this->addEdge(0, 1, '$'); //add a lambda egde between i and f (always 0 and 1)
}
        
void Automaton::addConcat(){}
void Automaton::addStar(){}
void Automaton::addChoice(){}

int main(){
    Automaton floepie(10);
    floepie.printGraph();
    
    return 0;
}
