/**
* Automaton: a directed, weighted graph describing a regular expression
* @author Eva van Houten (s1478621)
* @author David Kleingeld (s1432982)
* @file Automaton.h
* @date 08-12-2016
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
    /**
    * @function toDot
    * @abstract output the automaton to a dot file
    * @param filename the file to output to
    * @return a boolean to signal success
    **/
    bool toDot(std::string filename);
    /**
    * @function checkString
    * @abstract checks if a string fulfills the automaton's regex
    * @param toCheck the string to check
    * @param curNode the node to start checking from (call with 0)
    * @return a boolean that is true if the string matches the expression
    **/
    bool checkString(std::string toCheck, int curNode);
    private:
    bool isChecked[numNodes];
};

#endif //AUTOMATON_H
