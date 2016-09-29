/**
* Class name: Boom, stack implemented using a singly connected list
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file Boom.h
* @date 20-09-2016
**/

#include <string>
#include <stack>

#ifndef Boom_h
#define Boom_h

class Boom {
public:
  /**
  * @function Boom()
  * @abstract Constructor: Create new object node
  * @param
  * @return object of class node
  * @pre 
  * @post 
  **/
  Boom();
//  /**
//  * @function ~Boom()
//  * @abstract Deconstructor: Deletes tree
//  * @param
//  * @return object of class node
//  * @pre 
//  * @post 
//  **/
//  ~Boom();
  /**
  * @function processInput()
  * @abstract
  * @param
  * @return
  * @pre 
  * @post 
  **/
	void processInput(std::string substring);
	void walkInorder();
private:
	//Type of a leaf/node
	enum typeOfLeaf { PLUS, MINUS, TIMES, POWER, DEVIDE, 
									  NUMBER, VARIABLE, SIN, COS, PI };
	//Struct for the leaves/nodes
	struct Leaf {
		Leaf();
		Leaf* branchLeft;
		Leaf* branchRight;

		typeOfLeaf operand;
		
		union{
		  char variable;
		  double number;
  	};
	};
	//Stack of leaves
  std::stack<Leaf*> leafStack;
	//Root of the tree
  Leaf* root;//TODO if multiwalk not necessairy we can set currentleaf to this when done
	//Current leaf/node
	Leaf* currentLeaf;
  /**
  * @function nextFreeBranch()
  * @abstract 
  * @param
  * @return 
  * @pre 
  * @post 
  **/
	void nextFreeBranch();
  /**
  * @function stringIsNumber()
  * @abstract 
  * @param
  * @return 
  * @pre 
  * @post 
  **/
	bool stringIsNumber(std::string substring);
  /**
  * @function addLeaf(typeOfLeaf operand, char variable, double number)
  * @abstract 
  * @param typeOfLeaf operand, char variable, double number
  * @return 
  * @pre 
  * @post 
  **/
	void addLeaf(typeOfLeaf operand, char variable, double number);
	//TODO: Display tree: Expression 
	void display(typeOfLeaf operand);
	//TODO: Display tree: Graphic
	//TODO: Destructor
};

#endif
