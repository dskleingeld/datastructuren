#include "Graph.h"
#include "Automaton.h"
#include "Boom.h"

Boomaton::Boomaton(int numNodes, Leaf* root) : Graph(numNodes){
    numNodes = numNodes;
    addEdge(0, 1, root); //add the tree to the initial edge
    processOperation(0, 1);
}
        
void Boomaton::addConcat(int start, int end, Leaf* concatNode){
    removeEdge(start, end);
    addEdge(start, lastGraphNode+1, concatNode->left);
    addEdge(lastGraphNode+1, end, concatNode->right);
}

void Boomaton::addStar(int start, int end, Leaf* operationNode){
    
}

void Boomaton::addChoice(int start, int end, Leaf* operationNode){
    
}

void Boomaton::nextLayer(int start, int end, Leaf* operationNode){
    if(operationNode->left){
        processOperation(start, end, operationNode->left);
    }
    if(operationNode->right){
        processOperation(start, end, operationNode->right);
    }
}

void Boomaton::processOperation(int start, int end){
    AdjListNode* prevNode;
    operationNode = findEdge(start, end, prevNode)->edgeVal; //get the edgeVal of the edge between start and end (this is a Leaf*)
    switch(operationNode->operand){
        case CONCAT:
            addConcat(start, end, operationNode);
            break;
        case REPETITION:
            addStar(start, end, operationNode);
            break;
        case OR:
            addStar(start, end, operationNode);
            break;
        case CHAR:
            nextLayer(start, end, operationNode);
    }
}

int main(){
    Boomaton floepie(10);
    floepie.printGraph();
    
    return 0;
}
