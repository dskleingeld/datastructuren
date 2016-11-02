/**
* Simplify: class definition, simplify the expression-tree
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file Simplify.h
* @date 2-11-2016
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

#include <Boom.h>

#ifndef Simplify_h
#define Simplify_h

class Evaluate : public Boom {
public:
	/**
	* @function CallSimplify
	* @abstract Public function to initiate the Simplify funcion
	**/	
private:
	// Number on 'left side' of calculation
	double left;
	// Number on 'right side' of calculation
	double right;
	// Variable used in calculation
	char var_left;
	char var_right;

	/**
	* @function Simplify
	* @abstract This function simplifies the expression
	* @return Simplified expression-tree
	* @pre Non-empty, non-simplified tree
	* @post Tree which only has numbers in nodes, not in leaves
	**/	

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
	void Operate(typeOfLeaf operand);
	/**
	* @function FindElement
	* @abstract What element is in the leaf?
	* @param
	**/
	void FindElement(Leaf* currentLeaf, double num, char var);

	void Plus();

	void Minus();

	void Times();

	void Power();

	void Devide();

	void Sin();

	void Cos();
};

#endif
