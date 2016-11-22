#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "Graph.h"

const int numNodes = 10;

class Automaton : public Graph{
    public:
        Automaton(int numNodes);
        
        void addConcat();
        void addStar();
        void addChoice();
};

#endif
