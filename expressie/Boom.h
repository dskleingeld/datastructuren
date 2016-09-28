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
  * @function add()
  * @abstract Check if object Boom is empty
  * @param
  * @return true (is empty) or false (is not empty)
  * @pre 
  * @post 
  **/
	void processInput(std::string substring);
private:

		
	enum typeOfLeaf { PLUS, MINUS, TIMES, POWER, DEVIDE, 
									  NUMBER, VARIABLE, SIN, COS, PI };

	struct Leaf {
		Leaf* branchLeft = NULL;
		Leaf* branchRight = NULL;

		typeOfLeaf operand;
		
		union{
		  char variable;
		  double number;
  	};
	};

  std::stack<Leaf*> leafStack;
	
  Leaf* root;//TODO if multiwalk not necessairy we can set currentleaf to this when done
	Leaf* currentLeaf;
	
	void nextFreeBranch();
	
	bool stringIsNumber(std::string substring);
	
	void addLeaf(typeOfLeaf operand, char variable, double number);
};



#endif
