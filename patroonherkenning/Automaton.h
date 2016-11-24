#ifndef AUTOMATON_H
#define AUTOMATON_H

/*This class contains the automaat, the automaat is made from a binairy tree
passed to the constructor of this class*/

#include "Graph.h"
#include "Boom.h"

const int numNodes = 100;

class Boomaton : public Graph<Leaf*>{
    public:
        Boomaton(int numNodes, Leaf* root);
        
        void addConcat(int start, int end, Leaf* concatNode);
        void addStar(int start, int end, Leaf* starNode);
        void addChoice(int start, int end, Leaf* choiceNode);
        
        void processOperation(int start, int end, Leaf* branch);
        
        
};
/*
class Automaton : public Graph<char>{
    public:
        Automaton(int numNodes, Leaf* root);
};
*/
#endif
