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

void Boom::Tree_building(std::string str, Leaf* ingang) {
  //ingang is a new empty pointer with nothing attached
  std::string str_left;
  std::string str_right;
  Leaf* goLeft = NULL;
  Leaf* goRight = NULL;
  std::cout << "str: " <<str<<std::endl;

  if (enclosed(str)) {
    str_left = str.substr(1, str.size() - 2);
    goLeft = ingang;
  }

  else if (repEnclosed(str)) {
    str_left = str.substr(1, str.size() - 3);
    build_rep_tree(ingang, goLeft);
  }
  else if (split_concat(str, str_left, str_right)) {
    build_concat_tree(ingang, goLeft, goRight);
  }
  else if (split_or(str, str_left, str_left)) {
    build_or_tree(ingang, goLeft, goRight);
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
    std::cerr << "Unrecognised structure" << str << std::endl;
  }
  //std::cout<<goLeft<<" "<<goRight<<"\n";
  if (goLeft != NULL) {db("-> going left\n"); Tree_building(str_left, goLeft);}
  db("entering second part of recur.\n")
  if (goRight != NULL) {db("-> going right\n"); Tree_building(str_right, goRight);}
  
  db("->going up one level\n")
}

bool Boom::enclosed(std::string str) {
  db("checking if enclosed\n")
  if((str[0]=='(') && (str.back()==')')) return true;
  else return false;
}

bool Boom::repEnclosed(std::string str) {
  db("checking if repeated enclosed\n")
  if(str.size()>2) {
    std::string str_ending = str.substr(str.size() - 2); //get last 2 chars of string
    if ((str[0] == '(') && (str_ending == ")*")) return true;
  }
  else return false;
  return false;
}

bool Boom::oneLetter(std::string str) {
  db("checking if only one letter\n")
  if(str.size()==1) return true;
  else return false;
}

bool Boom::repOneLetter(std::string str) {
  db("checking if repeated one letter\n")
  if((str.size()==2) & (str[1]=='*')) return true;
  else return false;
}

bool Boom::split_concat(const std::string str, std::string &str_left, std::string &str_right) {
  db("checking if concatenation\n")
  unsigned int strSize = (unsigned int) str.size();

  if (strSize < 2) return false;
  else {
    unsigned int i = 1;

    while (i < strSize) {
      if (((isalpha(str[i - 1])) | (str[i - 1] == ')')) & (isalpha(str[i]) | str[i])) {
        str_left = str.substr(0, i);
        str_right = str.substr(i, strSize - i);
        return true;
      } else i++;
    }
    return false;
  }
}

bool Boom::split_or(const std::string str, std::string &str_left, std::string &str_right) {
  db("checking if choice/or \n")
  unsigned int strSize = (unsigned int) str.size();

  if (strSize < 2) return false;
  else {
    unsigned int i = 0;

    while (i < strSize) {
      if (str[i] == '|') {
        //TODO really wierd stuff happening here NEED MIEL
        str_left = str.substr(0, i);
        std::cout<<str.substr(0,i);
        str_right = str.substr(i+1, strSize - i);
        std::cout<<"i, l&r: "<<i<<", "<<str_left<<", "<<str_right<<std::endl;
        return true;
      } else i++;
    }
    return false;
  }
}

void Boom::build_rep_tree(Leaf* ingang, Leaf*& goLeft) {
  db("*building repeating tree\n")
  ingang->operand = REPETITION;
  ingang->left = new Leaf;

  goLeft = ingang->left;
}

void Boom::build_concat_tree(Leaf* ingang, Leaf*& goLeft, Leaf*& goRight) {
  db("*building concat tree\n")
  ingang->operand = CONCAT;
  ingang->left = new Leaf;
  ingang->right = new Leaf;

  goLeft = ingang->left;
  goRight = ingang->right;
}

void Boom::build_or_tree(Leaf* ingang, Leaf*& goLeft, Leaf*& goRight) {
  db("*building or tree\n")
  ingang->operand = OR;
  ingang->left = new Leaf;
  ingang->right = new Leaf;

  goLeft = ingang->left;
  goRight = ingang->right;
}

void Boom::build_letter_tree(const std::string str, Leaf *ingang) {
  db("*building letter tree\n")
  ingang->operand = LETTER;
  ingang->letter = str[0];
}