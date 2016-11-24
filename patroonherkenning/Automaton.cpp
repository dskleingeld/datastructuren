#include "Graph.h"
#include "Automaton.h"
#include "Boom.h"


Boomaton::Boomaton(int numNodes, Leaf* root) : Graph(numNodes){
    numNodes = numNodes;
    addEdge(0, 1, root); //add the tree to the initial edge
    processOperation(0, 1, root);
}

void Boomaton::addConcat(int start, int end, Leaf* concatNode){
    removeEdge(start, end, concatNode);
    addEdge(start, lastGraphNode+1, concatNode->left);
    addEdge(lastGraphNode+1, end, concatNode->right);
    
    processOperation(start, lastGraphNode+1, concatNode->left);
    processOperation(lastGraphNode+1, end, concatNode->right);
}

void Boomaton::addStar(int start, int end, Leaf* starNode){
    Leaf* lambda = new Leaf;
    lambda->operand = LETTER;
    lambda->letter = '$';
    
    removeEdge(start, end, starNode);
    addEdge(start, end, starNode->left);
    addEdge(start, end, lambda);
    addEdge(end, start, lambda);
    
    processOperation(start, end, starNode->left);
}

void Boomaton::addChoice(int start, int end, Leaf* choiceNode){
    removeEdge(start, end, choiceNode);
    addEdge(start, end, choiceNode->left);
    addEdge(start, end, choiceNode->right);
    processOperation(start, end, choiceNode->left);
    processOperation(start, end, choiceNode->right);
}

void Boomaton::processOperation(int start, int end, Leaf* branch){
    switch(branch->operand){
        case CONCAT:
            addConcat(start, end, branch);
            break;
        case REPETITION:
            addStar(start, end, branch);
            break;
        case OR:
            addStar(start, end, branch);
            break;
        case LETTER:
            //done with this recursive step
            break;
    }
}
