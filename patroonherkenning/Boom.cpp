#include "Boom.h"

Boom::Boom(std::string expression) {
  //call the recursive Tree_building function with as its entrance point the root of the tree
  root = new Leaf;
  Tree_building(expression, root);
}

void Boom::Tree_building(std::string str, Leaf* ingang) {
  std::string str_left;
  std::string str_right = NULL;
  
  if(enclosed(str)){
    str_left = str.substr(1, str.size() -1);
  }
  else if(repEnclosed(str)){
    str_left = str.substr(1, str.size() -2);
    build_rep_tree(ingang);
  }
  else if(split_concat(str, str_left, str_right)){
    build_concat_tree(ingang);
  }
  else if(split_or(str, str_left, str_left)){
    build_or_tree(ingang);
  }
  else if(OneLetter(str)){
    build_letter_tree(str, ingang);
  }
  else if(RepOneLetter(str)){
    build_rep_tree(ingang);
    ingang = ingang->left;
    build_letter_tree(str, ingang);
  }
  else{
    std::stderr<<"Unrecognised structure"<<str;
  }
  
  Tree_building(str_left, ingang->left);
  if(str_right != NULL) Tree_building(str_right, ingang->right);
}

bool Boom::enclosed(std::string str) {
  if((str[0]=='(') && (str.back()==')')) return true;
  else return false;
}

bool Boom::repEnclosed(std::string str) {
  std::string str_ending = str.substr(str.size() -2) //get last 2 chars of string
  if((str[0]=='(') && (str_ending ==")*") && ) return true;
  else return false;
}

bool Boom::split_concat(std::string str, std::string &str_left, std::string &str_right) {
  int strSize = (int)str.size();
  
  if(strSize<2) return false;
  else{
    int i = 1;
    
    while(i < strSize) {
      str[i-1]
          //TODO
    }
  }
}