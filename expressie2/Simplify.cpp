/**
* Simplify: class implementation
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file Simplify.cpp
* @date 2-11-2016
**/

#include <cmath>
#include "Simplify.h"

void Simplify::Simp_inOrder(Leaf* Temp) {
	// When you enter inOrder, you are always at the first visit

	if (Temp) {

		Simp_inOrder(Temp->branchLeft); 
		//Entering second visit
		Simp_inOrder(Temp->branchRight);
		//At the end of inOrder, you are always at the third visit
		Operate(Temp.operand);

		// TODO alle code die hieronder staat met in aparte functies

		// Now we need to process this stuff
		// First check if we are dealing with variables
		// TODO where do we set these values to 0?
		if ((var_left != 0) && (var_right !=0)) { // both are variables
			if (var_right == var_left) {
				// do sthg				
			}
			else {
				// we can't simplify this expression
			}		
		}
		else if (var_left != 0) { // this is a variable
			if (right == 0) {
			// do sth				
			}
			if (right == 1) {
			// do sth				
			}
			else {
			// we can't simplify this expression
			}
		}
		else if (var_right != 0) { // this is a variable
			if (left == 0) {
			// do sth				
			}
			if (left == 1) {
			// do sth				
			}
			else {
			// we can't simplify this expression
			}
		}
		
		else { // they are numbers			
			Temp.number = left [Temp.operand] right
			Temp.operand = NUMBER;
		}
		
	}
	/**
	* Notes:
	* Mogelijke situaties (met a en b = getal):
	* pi = 3.14
	* cos(a)
	* sin(a)
	* a+b a+0, a-b, a*b a*0 a*1, a/b a/0
	* a^b, a^1, a^0
	**/
}

void Simplify::Operate(typeOfLeaf operand) {
	left = 0;
	var_left = 0;
	right = 0;
	var_right = 0;
	switch (operand) {
			case PLUS:
				FindElement(Temp->BranchLeft, left, var_left);
				FindElement(Temp->BranchRight, right, var_right);
				Plus();
				break;
			case MINUS:
				FindElement(Temp->BranchLeft, left, var_left);
				FindElement(Temp->BranchRight, right, var_right);
				Minus();
				break;
			case TIMES:
				FindElement(Temp->BranchLeft, left, var_left);
				FindElement(Temp->BranchRight, right, var_right);
				Times();
				break;			
			case POWER:
				FindElement(Temp->BranchLeft, left, var_left);
				FindElement(Temp->BranchRight, right, var_right);
				Power();
				break;				
			case DEVIDE:
				FindElement(Temp->BranchLeft, left, var_left);
				FindElement(Temp->BranchRight, right, var_right);
				Devide();
				break;
			case SIN:
				FindElement(Temp->BranchLeft, left, var_left);
				Sin();
				break;
			case COS:
				FindElement(Temp->BranchLeft, left, var_left);
				Cos();
				break;
			default:
				break;
	}
}

void Simplify::FindElement(Leaf* currentLeaf, double num, char var) {
	switch (currentLeaf.operand) {
		case PI:
			num = 3.14159265359;
			break;
		case VARIABLE:
			var = currentLeaf.variable;
			break;
		case NUMBER:
			num = currentLeaf.number;
			break;
		default:
			break;
	}
}

void Simplify::Plus() {

}

void Simplify::Minus() {

}

void Simplify::Times() {

}

void Simplify::Power() {

}

void Simplify::Devide() {

}

void Simplify::Sin() {

}

void Simplify::Cos() {

}
