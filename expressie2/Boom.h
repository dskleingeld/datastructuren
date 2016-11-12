/**
* Class name: Boom, stack implemented using a singly connected list
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file Boom.h
* @date 12-11-2016
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
	void simplify();
	/**
	* @function Evaluate
	* @abstract initiates the evaluation sequence
	* @param std::string variable: the variable which has value 'value'
	**/
	void evaluate(std::string variable, double value);
  /**
	* @function Differentiate
	* @abstract initiates the diffrentiation sequence
	* @param std::string toDiffTo: the variable to diffrentiate to
  **/
	void differentiate(char toDiffTo);
	/**
	* @function graph_dot
	* @abstract create a textfile to save the structure and information of the
	tree in order to display it graphically
	* @pre non-empty tree
	**/
	void graph_dot(std::string filename);
private:
	//Type of a leaf/node
	enum typeOfLeaf {
		PLUS, MINUS, TIMES, POWER, DEVIDE,
		NUMBER, VARIABLE, SIN, COS, PI, D, EMPTY //D is used as: d/d(var)
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
	void clear(Leaf* Temp);
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
	* @param typeOfLeaf operand: the type of operand in the node to be added, 
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
	* @param typeOfLeaf operand, Leaf* Temp, std::ofstream & myfile
	* @pre a non-empty node of the tree
	**/
	void writeLabel(typeOfLeaf operand, Leaf* Temp, std::ofstream & myfile);
	/**
	* @function graph_preOrder
	* @abstract traverse the tree in pre-order direction and write the 
	information from nodes and connections to a file
	* @param Leaf* Temp, std::ofstream & myfile: a textfile
	* @pre a non-empty node of the tree
	**/
	void graph_preOrder(Leaf* Temp, std::ofstream & myfile);
	/**
	* @function writeConnection
	* @abstract write connections between nodes to graph.txt
	* @param std::ofstream & myfile: a textfile, std::stack<int> myStack: 
	a stack to keep track of te nodes
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
	
/*	---- Simplify ----	*/
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
	void simp_inOrder(Leaf* Temp, Leaf* previous, bool isLeft);
	/**
	* @function FindOperand
	* @abstract What operand is in the current node?
	* @param operand
	**/
	void operate(Leaf* thisLeaf, Leaf* previous, bool isLeft);
	/**
	* @function FindElement
	* @abstract What element is in the leaf?
	* @param
	**/
	bool findElement(Leaf* thisLeaf, double &num, char &var);
	/**
	* @function plus
	* @abstract sums the values of this nodes' children
	* @param thisLeaf (current node)
	* @return true or false (if one or both children contain non-numerical value)
	**/
	bool plus(Leaf* thisLeaf);
	/**
	* @function minus
	* @abstract subtracts the values of this nodes' children
	* @param thisLeaf (current node)
	* @return true or false
	**/
	bool minus(Leaf* thisLeaf);
	/**
	* @function times
	* @abstract multiplies the values of this nodes' children
	* @param thisLeaf (current node)
	* @return true or false
	**/
	bool times(Leaf* thisLeaf);
	/**
	* @function power
	* @abstract left child ^ right child
	* @param thisLeaf (current node)
	* @return true or false
	**/
	bool power(Leaf* thisLeaf);
	/**
	* @function devide
	* @abstract devides the values of this nodes' children
	* @param thisLeaf (current node)
	* @return true or false
	**/
	bool devide(Leaf* thisLeaf);
	/**
	* @function sinus
	* @abstract sin(value in left child)
	* @param thisLeaf (current node)
	* @return true or false
	**/
	bool sinus(Leaf* thisLeaf);
	/**
	* @function cos
	* @abstract cos(value in left child)
	* @param thisLeaf (current node)
	* @return true or false
	**/
	bool cosinus(Leaf* thisLeaf);

/*	---- Evaluate ---- */
	/**
	* @function Evaluate
	* @abstract Go through the tree and replace every instance of x with the given number and simplify afterwards
	* @param double value: the value to fill in for x
	* @pre An expression tree with variable x in one or more of the nodes/leaves
	* @post An expression tree with a value for each variable x
	**/
	void eval_inOrder(Leaf* Temp, char variable, double value);

/*	---- Differentiate ---- */
	/**
	* @function diff_inOrder
	* @abstract Differentiate the tree in order
	* @param toDiffTo: the variable that we will be differentiating to (usually x)
	* current: current node
	* previous: previous node, with pointer to current node
	**/
	void diff_inOrder(char toDiffTo, Leaf* current, Leaf* previous, bool left);
	/**
	* @function variable
	* @abstract Differentiate current subtree containing a variable
	* @param toDiffTo: the variable that we will be differentiating to (usually x)
	* current: current node
	* previous: previous node, with pointer to current node
	* @return: subtree that is part of the differentiation
	**/
	Leaf* variable(char toDiffTo, Leaf* current, Leaf* previous);
	/**
	* @function constant
	* @abstract Differentiate current subtree containing a constant
	* @param toDiffTo, current, previous
	* @return: subtree
	**/
	Leaf* constant(char toDiffTo, Leaf* current, Leaf* previous);
	/**
	* @function quotientRule
	* @abstract Use quotient rule to differentiate current subtree
	* @param toDiffTo, current, previous
	* @return: subtree
	**/
	Leaf* quotientRule(char toDiffTo, Leaf* current, Leaf* previous);
	/**
	* @function sumRule
	* @abstract Use sum rule to differentiate current subtree
	* @param toDiffTo, current, previous
	* @return: subtree
	**/
	Leaf* sumRule(char toDiffTo, Leaf* current, Leaf* previous);
	/**
	* @function productRule
	* @abstract Use product rule to differentiate current subtree
	* @param toDiffTo, current, previous
	* @return: subtree
	**/
	Leaf* productRule(char toDiffTo, Leaf* current, Leaf* previous);
	/**
	* @function powerRule
	* @abstract Use product rule to differentiate current subtree
	* @param toDiffTo, current, previous
	* @return: subtree
	**/
	Leaf* powerRule(char toDiffTo, Leaf* current, Leaf* previous);
	/**
	* @function cosRule
	* @abstract Differentiate current subtree containing a cosine
	* @param toDiffTo, current, previous
	* @return: subtree
	**/
	Leaf* cosRule(char toDiffTo, Leaf* current, Leaf* previous);
	/**
	* @function sinRule
	* @abstract Differentiate current subtree containing a sinus
	* @param toDiffTo, current, previous
	* @return: subtree
	**/
	Leaf* sinRule(char toDiffTo, Leaf* current, Leaf* previous);

/* ---- Additional functions  ---- */

	/**
	* @function calc_sum
	* @abstract function to calculate the sum of two numbers in seperate leaves
	* @param Leaf* a, typeOfLeaf a_operand, Leaf* b, typeOfLeaf b_operand
	* @return a + b
	**/
	int calc_sum(Leaf* a, typeOfLeaf a_operand, Leaf* b, typeOfLeaf b_operand);
	/**
	* @function deepSummation
	* @abstract function to calculate a two-level summation, for example: (4 + x) + 2 = 6 + x
	* @param Leaf* current, bool& success
	* @return the current node of type Leaf
	**/
	Leaf* deepSummation(Leaf* current, bool& success);
	/**
	* @function setToZero
	* @abstract set number of current node to 0 and operand to NUMBER
	* @return the current node of type Leaf
	**/
	Leaf* setToZero();
	/**
	* @function setToOne
	* @abstract set number of current node to 1 and operand to NUMBER
	* @return the current node of type Leaf
	**/
	Leaf* setToOne();
	/**
	* @function isNearlyEqual
	* @abstract function to check whether two doubles are equal
	* @param double x, double y: the doubles to compare
	* @return true (are equal), false (are not equal)
	**/
	bool isNearlyEqual(double x, double y);
	/**
	* @function copyLeaf
	* @abstract copy values of current leaf
	* @param x and y of type Leaf
	**/
	void copyLeaf(Leaf* x, Leaf* y);
	/**
	* @function recDeepcopy
	* @abstract recursively copy current node and all its children
	* @param x and y of type Leaf
	**/
	void recDeepcopy(Leaf* x, Leaf* y);
	/**
	* @function deepcopy
	* @abstract make deep copy of current node and all its children
	* @param x of type Leaf
	* @return the current node of type Leaf
	**/
	Boom::Leaf* deepcopy(Leaf* x);
	/**
	* @function contains_var
	* @abstract check if current leaf contains the given variable
	* @param current: current leaf, found_var: boolean that is initially false, 
	* toDiffTo: the character that we will be differentiating to
	* @pre: found_var = false
	* @post: found_var = true
	**/
	void contains_var(Leaf* current, bool& found_var, char toDiffTo);
};

#endif
