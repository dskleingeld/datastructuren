/**
* Automaton: a directed, weighted graph describing a regular expression
* @author Eva van Houten (s1478621)
* @author David Kleingeld (s1432982)
* @file Automaton.h
* @date datum laatste wijziging
**/

#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "Graph.h"
#include "Boom.h"

const int numNodes = 100;

//In-between step to ensure a clean Automaton in the end that only consists of a char Graph. Boomaton has edges that are parts of the tree.
class Boomaton : public Graph<Leaf*>{
    friend class Automaton;
    
    protected:
    Boomaton(Leaf* root);
    
    void addConcat(int start, int end, Leaf* concatNode);
    void addStar(int start, int end, Leaf* starNode);
    void addChoice(int start, int end, Leaf* choiceNode);
    
    void processOperation(int start, int end, Leaf* branch);
};

//Child class of Graph, contains the automaton made from the regex
class Automaton : public Graph<char>{
    public:
    /**
    * @function Automaton
    * @abstract (constructor) turn the supplied regex tree into an automaton
    * @param root a pointer to the root of the regex tree
    * @return an Automaton object that implements the regex
    **/
    Automaton(Leaf* root);
    bool toDot(std::string filename);
};

#endif //AUTOMATON_H
