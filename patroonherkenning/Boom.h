/**
* Boom: the binary parse tree of a regular expression
* @author Eva van Houten (s1478621)
* @author David Kleingeld (s1432982)
* @file Boom.h
* @date fri 25/11/2016
**/

#ifndef BOOM_H
#define BOOM_H

#include <string>

/*tree element*/
enum Operand {
    LETTER, OR, REPETITION, CONCAT
};
//Struct for the leaves/nodes
struct Leaf {
  Leaf(){
    left = nullptr;
    right = nullptr;
  }
  Leaf* left;
  Leaf* right;

  Operand operand;
  char letter;
};

class Boom
{
  public:
    /*takes a string and creates a binairy tree from pointers storing the structure of the tree*/
    
    /**
     * @function Boom
     * @abstract a binairy tree that represents an regular expression
     * @param expression is a standard lib string that represents the expression
     * @pre an empty Boom class
     * @post a pointer root with a binairy tree attached
    **/
    Boom(std::string expression);

    /**
     * @function getRoot
     * @abstract gives the user the pointer to the binairy tree
     * @return pointer to the root element of the regex tree
    **/
    Leaf* getRoot();
    
  private:
    //keeps track of starting point of the tree
    Leaf* root;
    
    /**
     * @function Tree_building
     * @abstract walks through the regular expression string recursively adding
     *           elements following the order of operation of regex
     * @param str is a standard lib string that represents the expression to
     *        be added. Ingang is a pointer where to attach the tree 
     * @pre one or more element in the tree.
     * @post a tree with another subtree attached or the complete tree if the 
     *       recursion is done
    **/
    const void Tree_building(const std::string str, Leaf* ingang);   
    /**
     * @function enclosed
     * @abstract check if the string is completely enclosed
     * @param str is a string that represents the (sub) expression to evaluate
     * @return true if enclosed false if not
    **/
    const bool enclosed(const std::string str);
    /**
     * @function repEnclosed
     * @abstract check if a substring is enclosed with repetition (enclosed by 
     *           breackts with after the ending bracket a repetition character
     * @param str is a string that represents the (sub) expression to evaluate
     * @return true if enclosed with repetition false if not
    **/
    const bool repEnclosed(const std::string str);
    /**
     * @function oneLetter
     * @abstract check if the remaining substring is only a letter 
     * @param str is a string that represents the (sub) expression to evaluate
     * @return true if only a letter otherwise false if not
    **/    
    const bool oneLetter(const std::string str);
    /**
     * @function repOneLetter
     * @abstract check if the remaining substring is a letter followed by repetition 
     * @param str is a string that represents the (sub) expression to evaluate
     * @return true if only a letter+repetition false if not
    **/    
    const bool repOneLetter(const std::string str);
    /**
     * @function split_concat
     * @abstract check if there is a concatenation in the remaining substring if
     *           there is split the substring into 2 parts
     * @param str is a string that represents the (sub) expression to evaluate
     * @return true if there is a concatenation
     * @pre 2 variables str_left en str_right
     * @post str_left containing the part of the substring before the concatenation
     *       str_right containing the part of the substring after concatenation
    **/       
    const bool split_concat(const std::string str, std::string& str_left, std::string& str_right);
    /**
     * @function split_or
     * @abstract check if there is an or operator in the remaining substring if
     *           there is split the substring into 2 parts
     * @param str is a string that represents the (sub) expression to evaluate
     * @return true if there is an or operator
     * @pre 2 variables str_left en str_right
     * @post str_left containing the part of the substring before the concatenation
     *       str_right containing the part of the substring after concatenation
    **/       
    const bool split_or(const std::string str, std::string& str_left, std::string& str_right);
 
 
    /**
     * @function build_rep_tree
     * @abstract sets an unset node to 'repetition' and creates 1 new node
     * @param ingang is the pointer to the unset node, goLeft is an empty pointer
     * @pre goLeft an empty pointer
     * @post a tree with an unset node set to 'repetition' and another unset node
     *       added below the 'repetition' node, the added nodes adress stored in goLeft
    **/   
    const void build_rep_tree(Leaf* ingang, Leaf*& goLeft);
    /**
     * @function build_rep_tree
     * @abstract sets an unset node to 'concatenation' and creates 2 new nodes 
     * @param ingang is the pointer to the unset node, goLeft and goRight are
     *        empty pointers
     * @pre goLeft and goRight empty pointers
     * @post a tree with an unset node set to 'concatenation' and two new unset
     *       nodes added below the 'concatenation' node with theire adresses 
     *       stored in goLeft and goRight
    **/  
    const void build_concat_tree(Leaf* ingang, Leaf*& goLeft, Leaf*& goRight);
    /**
     * @function build_or_tree
     * @abstract sets an unset node to 'or' and creates 2 new nodes 
     * @param ingang is the pointer to the unset node, goLeft and goRight are
     *        empty pointers
     * @pre goLeft and goRight empty pointers
     * @post a tree with an unset node set to 'or' and two unset nodes added with
     *       adress stored in goLeft and goRight
    **/ 
    const void build_or_tree(Leaf* ingang, Leaf*& goLeft, Leaf*& goRight);
    /**
     * @function build_or_tree
     * @abstract sets a unset node to letter type and stores the specific letter 
     * @param ingang is the pointer to the unset node, str is a string containing
     *        one letter.
     * @pre one unset node
     * @post unset node set to type letter and the specific letter set 
    **/ 
    const void build_letter_tree(const std::string str, Leaf* ingang);
  };


#endif // BOOM_H
