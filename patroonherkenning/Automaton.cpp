/**
* Automaton: a directed, weighted graph describing a regular expression
* @author Eva van Houten (s1478621)
* @author David Kleingeld (s1432982)
* @file Automaton.cpp
* @date 08-12-2016
**/

#include <string>
#include <fstream>
#include "Graph.h"
#include "Automaton.h"
#include "Boom.h"

Boomaton::Boomaton(Leaf* root){
    addEdge(0, 1, root); //add the tree to the initial edge
    processOperation(0, 1, root); //start processing the tree
}

void Boomaton::addConcat(int start, int end, Leaf* concatNode){
    int newNode = lastGraphNode+1;
    removeEdge(start, end, concatNode);
    addEdge(start, newNode, concatNode->left);
    addEdge(newNode, end, concatNode->right);
    
    processOperation(start, newNode, concatNode->left);
    processOperation(newNode, end, concatNode->right);
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
            addChoice(start, end, branch);
            break;
        case LETTER:
            //done with this recursive step
            break;
    }
}

Automaton::Automaton(Leaf* root){
    Boomaton boomaton(root);
    for(int i=0; i<=boomaton.lastGraphNode; i++){
        AdjListNode<Leaf*>* follower = boomaton.list[i].firstAdjNode;
        while(follower){
            Leaf* edge = follower->edgeVal;
            int dest = follower->destination;
            addEdge(i, dest, edge->letter);
            follower = follower->next;
        }
    }
}

bool Automaton::toDot(std::string filename) {
	std::ofstream myfile;
	myfile.open(filename.c_str());
	if (myfile.is_open()) {
		myfile << "digraph G {\nrankdir=\"LR\"" << std::endl;
        myfile << "0 [label=\"i\"]" <<std::endl;
        myfile << "1 [label=\"f\"]" <<std::endl;
		for(int i=0; i<=lastGraphNode; i++){
            AdjListNode<char>* follower = list[i].firstAdjNode;
            while(follower){
                char edge = follower->edgeVal;
                int dest = follower->destination;
                myfile << i << " -> "<< dest << " [label=\"" << edge << "\"]\n";
                follower = follower->next;
            }
        }
        
		myfile << "}";
		myfile.close();
        return true;
	}
    return false;
}

bool Automaton::checkString(std::string toCheck, int curNode){
    if(curNode == 1 && toCheck == ""){
        return true;
    }
    
    int lambdaClosure[numNodes]; //keeps track of nodes reachable by 'empty' edges
    int numLambdas = 0;
    int charClosure[numNodes];
    int numChars = 0;
    
    AdjListNode<char>* follower = list[curNode].firstAdjNode;
    while(follower){
        if(follower->edgeVal == '$'){
            lambdaClosure[numLambdas] = follower->destination;
            numLambdas++;
        } else if(follower->edgeVal == toCheck[0]){
            charClosure[numChars] = follower->destination;
            numChars++;
        }
        follower = follower->next;
    }
    for(int i=0; i<numLambdas; i++){
        int node = lambdaClosure[i];
        #ifdef DEBUG
        std::cout << toCheck << " lambda from " << curNode << " to " << node << std::endl;
        #endif
        if(!isChecked[node]){
            isChecked[curNode] = true; //we are leaving by a lambda edge, so if we return here without chars there is no path
            if(checkString(toCheck, node)){
                #ifdef DEBUG
                std::cout << toCheck << " LAMBDA " << node << std::endl;
                #endif
                return true;
            }
        }
    }
    for(int i=0; i<numChars; i++){
        int node = charClosure[i];
        #ifdef DEBUG
        std::cout << toCheck << " from " << curNode << " to " << node << std::endl;
        #endif
        for(int i=0; i<numNodes; i++){
            isChecked[i] = false; //as soon as we travel by char, all checked nodes are free again
        }
        if(checkString(toCheck.erase(0, 1), node)){
            #ifdef DEBUG
            std::cout << toCheck << " CHAR " << node << std::endl;
            #endif
            return true;
        }
    }
    
    return false;
}
                
