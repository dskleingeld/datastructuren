#ifndef BOOM_H
#define BOOM_H
/*This class contains a tree that is made from raw text input.*/

#include <string>

class Boom
{
  public:
    /*takes a string and creates a binairy tree from pointers storing the structure of the tree*/
    Boom(std::string expression);
    
    /*tree element*/;
    enum Operand {
        LETTER, OR, REPETITION, CONCAT
    };
    //Struct for the leaves/nodes
    struct Leaf {
        Leaf();
        Leaf* left;
        Leaf* right;
        
        Operand operand;
        char letter;
    };
    
    //keeps track of starting point of the tree
    Leaf* root;
    
  private:
    
    /*recursively called function that takes a (sub) string and builds a pointer tree
     * with its (sub) root attached at the pointer ingang*/
    void Tree_building(std::string str, Leaf* ingang);
    
    /*check if a substring is enclosed by breackts*/
    bool enclosed(std::string str);
    /*check if a substring is enclosed by breackts and has repetition*/
    bool repEnclosed(std::string str);
    
    /*check if the remaining substring is only a letter*/
    bool OneLetter(std::string str);
    /*check if a letter with repetition*/
    bool RepOneLetter(std::string str);
    
    /*returns if there is a concatanation in the substring, if yes changes left and right to the
     * left and right part around the first found concatanation*/
    bool split_concat(std::string str, std::string& str_left, std::string& str_right);
    /*returns if there is a choice (or) in the substring, if yes changes left and right to the
     * left and right part around the first found 'or'*/
    bool split_or(std::string str, std::string& str_left, std::string& str_right);
    
    /*Adds a repetition leaf, then recusively by Tree_building the 'to be repeated part' is added
     * for this to work with the recusion of Tree_building the to be attached substring needs to be
     * rememberd in Tree_building*/
    void build_rep_tree(Leaf* ingang);
    /*Adds a leaf of type CONCAT, for this left and right substring need to be rememberd too*/
    void build_concat_tree(Leaf* ingang);
    /*Adds a leaf of type OR, left and right again need to be passed along nicely*/
    void build_or_tree(Leaf* ingang);
    /*Build the subtree for a single letter (just a leaf)*/
    void build_letter_tree(std::string str, Leaf* ingang)
  };


#endif // BOOM_H
