/**
* Boom: the binary parse tree of a regular expression
* @author Eva van Houten (s1478621)
* @author David Kleingeld (s1432982)
* @file Boom.cpp
* @date fri 25/11/2016
**/

#include <iostream>
#include "Boom.h"

#ifdef DEBUG
#define db(x) std::cerr << x;
#else
#define db(x)
#endif

Boom::Boom(std::string expression) {
  //call the recursive Tree_building function with as its entrance point the root of the tree
  root = new Leaf;

  Tree_building(expression, root);
  db("done with building initial tree")
}

Leaf* Boom::getRoot(){
  return root;
}

const void Boom::Tree_building(const std::string str, Leaf* ingang) {
  //ingang is a new empty pointer with nothing attached
  std::string str_left;
  std::string str_right;
  Leaf* goLeft = nullptr;
  Leaf* goRight = nullptr;

  if (enclosed(str)) {
    str_left = str.substr(1, str.size() - 2);
    goLeft = ingang;
  }
  else if (repEnclosed(str)) {
    str_left = str.substr(1, str.size() - 3);
    build_rep_tree(ingang, goLeft);
  }
  else if (split_or(str, str_left, str_right)) {
    build_or_tree(ingang, goLeft, goRight);
  }
  else if (split_concat(str, str_left, str_right)) {
    build_concat_tree(ingang, goLeft, goRight);
  }
  //both oneLetter functions handle all left string work.
  //further recursion stops here
  else if (oneLetter(str)) {
    build_letter_tree(str, ingang);
  }
  else if (repOneLetter(str)) {
    build_rep_tree(ingang, ingang); //ingang changed here
    build_letter_tree(str, ingang);
  }
  else {
    std::cerr << "Unrecognised structure: " << str << std::endl;
  }
  if (goLeft != nullptr) {db("-> going left\n"); Tree_building(str_left, goLeft);}
  db("entering second part of recur.\n")
  if (goRight != nullptr) {db("-> going right\n"); Tree_building(str_right, goRight);}
  
  db("->going up one level\n")
}

const bool Boom::enclosed(std::string str) {
  unsigned int bracketLevel = 0;
  unsigned int strSize = (unsigned int)str.size();

  db("checking if enclosed\n")
  if((str[0]=='(') && (str.back()==')')) {
    //trace the bracket level from the begin to almost the end of the string.
    //if it drops to zero anywhere the outermost brackets are not matching
    for(unsigned int i=1; i<strSize; i++){
      if(str[i-1]=='(') bracketLevel++;
      else if(str[i-1]==')') bracketLevel--;
      if(bracketLevel == 0) return false;
    }
    return true;
  }
  return false;
}

const bool Boom::repEnclosed(std::string str) {
  unsigned int bracketLevel = 0;
  unsigned int strSize = (unsigned int)str.size();

  db("checking if repeated enclosed\n")
  if(strSize>2) {
    std::string str_ending = str.substr(str.size() - 2); //get last 2 chars of string
    if ((str[0] == '(') && (str_ending == ")*")) {
      //trace the bracket level from the begin to almost the end of the string.
      //if it drops to zero anywhere the outermost brackets are not matching
      for(unsigned int i=1; i<strSize-1; i++){
        if(str[i-1]=='(') bracketLevel++;
        else if(str[i-1]==')') bracketLevel--;
        if(bracketLevel == 0) return false;
      }
      return true;
    }
    else return false;
  }
  else return false;
}

const bool Boom::oneLetter(std::string str) {
  db("checking if only one letter\n")
  if(str.size()==1) return true;
  else return false;
}

const bool Boom::repOneLetter(std::string str) {
  db("checking if repeated one letter\n")
  if((str.size()==2) & (str[1]=='*')) return true;
  else return false;
}

const bool Boom::split_concat(const std::string str, std::string &str_left, std::string &str_right) {
  db("checking if concatenation\n")
  unsigned int strSize = (unsigned int) str.size();
  unsigned int bracketLevel = 0;

  if (strSize < 2) return false;
  else {
    unsigned int i = 1;

    if(str[0]=='(') bracketLevel = 1;
    while (i < strSize) {
      char cur = str[i];
      char prev = str[i-1];

      //check if we are leaving a bracket enclosed part of the string
      if (str[i] == ')') bracketLevel--;

      //if the current part does not belong to a bracket enclosed section
      if (bracketLevel == 0) {
        //check if there is a concatenation
        if ( (isalpha(prev) && isalpha(cur)) |
             (isalpha(prev) && cur=='(')     |
             (prev==')'     && cur=='(')     |
             (prev=='*'     && isalpha(cur)) |
             (prev==')'     && isalpha(cur)) ) {
          //cut the concatenation into two separate parts
          str_left = str.substr(0, i);
          str_right = str.substr(i, strSize - i);
          return true;
        }
      }
      //check if we are entering a bracketed part of the string
      if (str[i] == '(') bracketLevel++;
      i++;
    }//end while
    return false;
  }
}


const bool Boom::split_or(const std::string str, std::string& str_left, std::string& str_right) {
  db("checking if choice/or \n")
  unsigned int strSize = (unsigned int) str.size();
  unsigned int bracketLevel = 0;

  std::string tempR;
  std::string tempL;

  if (strSize < 2) return false;
  else {
    unsigned int i = 0;

    while (i < strSize) {

      //check if we are leaving a bracket enclosed part of the string
      if (str[i] == ')') bracketLevel--;

      //if the current part does not belong to a bracket enclosed section
      if (bracketLevel == 0) {
        if (str[i] == '|') {
          str_left = str.substr(0, i);
          str_right = str.substr(i + 1);
          return true;
        }
      }
      //check if we are entering a bracket enclosed part of the string
      if (str[i] == '(') bracketLevel++;
      i++;
    }
  return false;
  }
}

const void Boom::build_rep_tree(Leaf* ingang, Leaf*& goLeft) {
  db("*building repeating tree\n")
  ingang->operand = REPETITION;
  ingang->left = new Leaf;

  goLeft = ingang->left;
}

const void Boom::build_concat_tree(Leaf* ingang, Leaf*& goLeft, Leaf*& goRight) {
  db("*building concat tree\n")
  ingang->operand = CONCAT;
  ingang->left = new Leaf;
  ingang->right = new Leaf;

  goLeft = ingang->left;
  goRight = ingang->right;
}

const void Boom::build_or_tree(Leaf* ingang, Leaf*& goLeft, Leaf*& goRight) {
  db("*building or tree\n")
  ingang->operand = OR;
  ingang->left = new Leaf;
  ingang->right = new Leaf;

  goLeft = ingang->left;
  goRight = ingang->right;
}

const void Boom::build_letter_tree(const std::string str, Leaf *ingang) {
  db("*building letter tree\n")
  ingang->operand = LETTER;
  ingang->letter = str[0];
}
