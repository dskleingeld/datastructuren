/**
* Class name: Boom, stack implemented using a singly connected list
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file Boom.h
* @date 03-11-2016
**/

/**
TODO remove this later
* @function functienaam
* @abstract beschrijving wat de functie doet,
inclusief hulpfuncties. Noem hulpfuncties niet!
* @param parameternaam beschrijving rol parameter
* @return beschrijving van het resultaat
* @pre exacte beschrijving preconditie
* @post exacte beschrijving postconditie
wat is er veranderd na het uitvoeren van de functie?
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
	/**
	* @function Simplify
	* @abstract initiates the simplifying sequence
	**/
	void Simplify();
	/**
	* @function Evaluate
	* @abstract initiates the evaluation sequence
	* @param std::string variable: the variable which has value 'value'
	**/
	void Evaluate(std::string variable, double value);
  /**
	* @function Differentiate
	* @abstract initiates the diffrentiation sequence
	* @param std::string toDiffTo: the variable to diffrentiate to
  **/
	void diff(char toDiffTo);
private:
	//Type of a leaf/node
	enum typeOfLeaf {
		PLUS, MINUS, TIMES, POWER, DEVIDE,
		NUMBER, VARIABLE, SIN, COS, PI, D //D is used as: d/d(var)
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
	
	
//	---- SIMPLIFY ----	
	// Number on 'left side' of calculation
	double left;
	// Number on 'right side' of calculation
	double right;
	// Variable used in calculation
	char var_left;
	char var_right;

	/**
	* @function Simp_InOrder
	* @abstract Walk through the tree with in-order traversion,
	* search for simplify-able expressions
	* @param Leaf* Temp is inherited from parent class Boom.h
	* When you start this function, Temp should be root (you start at 
	* the root of your tree).
	* @pre Non-empty tree of class Boom
	**/
	void Simp_inOrder(Leaf* Temp);

	/**
	* @function FindOperand
	* @abstract What operand is in the current node?
	* @param operand
	**/
	void Operate(Leaf* thisLeaf);
	/**
	* @function FindElement
	* @abstract What element is in the leaf?
	* @param
	**/
	bool FindElement(Leaf* thisLeaf, double &num, char &var);

	bool Plus(Leaf* thisLeaf);

	bool Minus(Leaf* thisLeaf);

	bool Times(Leaf* thisLeaf);

	bool Power(Leaf* thisLeaf);

	bool Devide(Leaf* thisLeaf);

	bool Sin(Leaf* thisLeaf);

	bool Cos(Leaf* thisLeaf);

	/**
	* @function isNearlyEqual
	* @abstract function to check whether two doubles are equal
	* @param double x, double y: the doubles to compare
	* @return true (are equal), false (are not equal)
	**/
	bool isNearlyEqual(double x, double y);

//	---- Evaluate ----
	/**
	* @function Evaluate
	* @abstract Go through the tree and replace every instance of x with the given number and simplify afterwards
	* @param double value: the value to fill in for x
	* @pre An expression tree with variable x in one or more of the nodes/leaves
	* @post An expression tree with a value for each variable x
	**/
	void Eval_inOrder(Leaf* Temp, char variable, double value);

	void diff_inOrder(char toDiffTo, Leaf* current);

	void variable(char toDiffTo, Leaf* current);

	void constant(char toDiffTo, Leaf* current);

	void quotientRule(char toDiffTo, Leaf* current);

	void sumRule(char toDiffTo, Leaf* current);

	void productRule(char toDiffTo, Leaf* current);

	void chainRule(char toDiffTo, Leaf* current);

	void copyLeaf(Leaf* x, Leaf* y);

	void recDeepcopy(Leaf* x, Leaf* y);

	Boom::Leaf* deepcopy(Leaf* x);

};

#endif
