/**
* Automaton: beschrijving van klasse/programma
* @author Eva van Houten (s1478621)
* @author David Kleingeld (s1432982)
* @file Automaton.h
* @date datum laatste wijziging
**/

#ifndef AUTOMATON_H
#define AUTOMATON_H

/*This class contains the automaton, which is made from a binary tree passed to its constructor. Boomaton is an in-between step where the edges of the automaton consist of parts of the binary tree.*/

#include "Graph.h"
#include "Boom.h"

const int numNodes = 100;

//In-between step to ensure a clean Automaton in the end that only consists of a char Graph.
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
    * @pre exacte beschrijving preconditie
    * @post exacte beschrijving postconditie
    wat is er veranderd na het uitvoeren van de functie?
    **/
    Automaton(Leaf* root);
};

#endif //AUTOMATON_H
