/**
* Class name: Boom, stack implemented using a singly connected list
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file Boom.h
* @date 12-10-2016
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
	* @return object of class node
	**/
	Boom();
 	/**
  * @function ~Boom()
  * @abstract Deconstructor
  **/
	~Boom();
	/**
	* @function processInput
	* @abstract process the input given by the user
	* @param std::string substring: a small part of the input
	**/
	void processInput(std::string substring);
	/**
	* @function view
	* @abstract calls the functions that display the tree in 2 different ways
	**/
	void view();
protected:
	//Type of a leaf/node
	enum typeOfLeaf {
		PLUS, MINUS, TIMES, POWER, DEVIDE,
		NUMBER, VARIABLE, SIN, COS, PI
	};
	//Struct for the leaves/nodes
	struct Leaf {
		Leaf();
		Leaf* branchLeft;
		Leaf* branchRight;

		typeOfLeaf operand;

		union {
			char variable;
			double number;
		};
	};
	//Stack of leaves
	std::stack<Leaf*> leafStack;
	//An extra stack for the Graphical_display function
	std::stack<int> Graph_Stack;
	//Root of the tree
	Leaf* root;
	//Current leaf/node
	Leaf* currentLeaf;
private:
	int counter;
 	/**
  * @function Clear
  * @abstract Deletes the nodes of the tree, recursively
  * @param Leaf* Temp
  * @pre Tree of size n
  * @post No tree
  **/
	void Clear(Leaf* Temp);
	/**
	* @function nextFreeBranch
	* @abstract searches for the next free branch on the right side, up from the 
		current position
	**/
	void nextFreeBranch();
	/**
	* @function stringIsNumber
	* @abstract check if the given string is a number
	* @param std::string substring
	* @return true: it is a number or false: it is not a number
	**/
	bool stringIsNumber(std::string substring);
	/**
	* @function addLeaf
	* @abstract create a new leaf at the current position and determine how many 
		children it needs
	* @param 	typeOfLeaf operand: the type of operand in the node to be added, 
						char variable: the variable in the node (if it is not an operand), 
						double number
	* @pre a tree with n nodes
	* @post a tree with n+1 nodes
	**/
	void addLeaf(typeOfLeaf operand, char variable, double number);
	/**
	* @function display
	* @abstract display the tree as a mathematical expression
	* @param typeOfLeaf operand, Leaf* Temp
	* @pre non-empty tree
	**/
	void display(typeOfLeaf operand, Leaf* Temp);
	/**
	* @function inOrder
	* @abstract traverse the tree in in-order direction
	* @param Leaf* Temp: a temporary Leaf object
	* @pre a non-empty node of the tree
	**/
	void inOrder(Leaf* Temp);
	/**
	* @function writeLabel
	* @abstract write the label of the node to graph.txt
	* @param 	typeOfLeaf operand, Leaf* Temp, 
						std::ofstream & myfile
	* @pre a non-empty node of the tree
	**/
	void writeLabel(typeOfLeaf operand, Leaf* Temp, std::ofstream & myfile);
	/**
	* @function Graph_preOrder
	* @abstract traverse the tree in pre-order direction and write the 
		information from nodes and connections to a file
	* @param 	Leaf* Temp, 
						std::ofstream & myfile: a textfile
	* @pre a non-empty node of the tree
	**/
	void Graph_preOrder(Leaf* Temp, std::ofstream & myfile);
	/**
	* @function Graph_display
	* @abstract create a textfile to save the structure and information of the 
		tree in order to display it graphically
	* @pre non-empty tree
	**/
	void Graph_display();
	/**
	* @function writeConnection
	* @abstract write connections between nodes to graph.txt
	* @param 	std::ofstream & myfile: a textfile, 
						std::stack<int> myStack: a stack to keep track of te nodes
	* @pre a non-empty node of the tree
	**/
	void writeConnection(std::ofstream & myfile, std::stack<int> myStack);
	/**
	* @function isOperator
	* @abstract check if operand is plus or minus
	* @param Leaf* Temp
	* @return True (is operator) or false
	**/
	bool isOperator(Leaf* Temp);
	/**
	* @function isUnaryOperator
	* @abstract check if operand is cos, sin or power
	* @param Leaf* Temp
	* @return True (is unary operator) or false
	**/
	bool isUnaryOperator(Leaf* Temp);
};

#endif
