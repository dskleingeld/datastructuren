/**
* Simplify: class implementation
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file Simplify.cpp
* @date 2-11-2016
**/

#include <cmath>
#include "Simplify.h"

Simplify::Simplify() {

}

Simplify::Leaf::Leaf() {

}

void Simplify::Simp_inOrder(Leaf* Temp) {
	// When you enter inOrder, you are always at the first visit
	if (Temp) {
		Simp_inOrder(Temp->branchLeft); 
		//Entering second visit
		Simp_inOrder(Temp->branchRight);
		//At the end of inOrder, you are always at the third visit
		Operate(Temp);
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

void Simplify::Operate(Leaf* thisLeaf) {
	left = 0;
	var_left = 0;
	right = 0;
	var_right = 0;
	switch (thisLeaf.operand) {
			case PLUS:
				FindElement(thisLeaf->BranchLeft, left, var_left); // Find the number on the left, TODO what happens if not a number?
				FindElement(thisLeaf->BranchRight, right, var_right); // Find the number on the right
				if ((var_left != 0) || (var_right != 0)) { // one of them is a variable
				    break;
			    }
				Plus(); // Calculate summation
				break;
			case MINUS:
				FindElement(thisLeaf->BranchLeft, left, var_left);
				FindElement(thisLeaf->BranchRight, right, var_right);
				if (Minus(thisLeaf)) {
				    thisLeaf->BranchLeft = NULL;
				    thisLeaf->BranchRight = NULL;
				    //TODO is this the right way to delete children?
				}
				break;
			case TIMES:
				FindElement(thisLeaf->BranchLeft, left, var_left);
				FindElement(thisLeaf->BranchRight, right, var_right);
				Times();
				break;			
			case POWER:
				FindElement(thisLeaf->BranchLeft, left, var_left);
				FindElement(thisLeaf->BranchRight, right, var_right);
				Power();
				break;				
			case DEVIDE:
				FindElement(thisLeaf->BranchLeft, left, var_left);
				FindElement(thisLeaf->BranchRight, right, var_right);
				if (Devide()) {
				    thisLeaf->BranchLeft = NULL;
				    thisLeaf->BranchRight = NULL;
				    //TODO is this the right way to delete children?				
				}
				break;
			case SIN:
				FindElement(thisLeaf->BranchLeft, left, var_left);
				Sin();
				break;
			case COS:
				FindElement(thisLeaf->BranchLeft, left, var_left);
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

bool Simplify::Minus(Leaf* thisLeaf) {
    if ((var_left != 0) && (var_right !=0)) { // both are variables
		if (var_right == var_left) {
			thisLeaf.number = 0;
			thisLeaf.variable = 0;
			thisLeaf.operand = NUMBER;
		}
		else {
			return false; // we can't simplify this expression
		}		
	}
	else if (var_left != 0) { // this is a variable
		if (right == 0) {
		    thisLeaf.number = 0;
			thisLeaf.variable = var_left;
			thisLeaf.operand = VARIABLE;		
		}
		else {
            return false; // we can't simplify this expression
		}
	}
	else if (var_right != 0) { // this is a variable
		if (left == 0) {
            thisLeaf.number = 0;
			thisLeaf.variable = var_right;
			thisLeaf.operand = VARIABLE;	
		}
		else {
            return false; // we can't simplify this expression
		}
	}
	
	else { // they are numbers			
		thisLeaf.number = left - right;
		thisLeaf.operand = NUMBER;
	}
	return true;
}

void Simplify::Times() {

}

void Simplify::Power() {

}

void Simplify::Devide(Leaf* thisLeaf) {
	if ((var_left != 0) && (var_right !=0)) { // both are variables
		if (var_right == var_left) {
			thisLeaf.number = 1;
			thisLeaf.variable = 0;
			thisLeaf.operand = NUMBER;				
		}
		else {
            return false; // we can't simplify this expression
		}		
	}
	else if (var_left != 0) { // this is a variable
		if (right == 0) {
		    //TODO can't devide by zero
		    return false;				
		}
		if (right == 1) {
		    thisLeaf.number = 0;
			thisLeaf.variable = var_left;
			thisLeaf.operand = VARIABLE;								
		}
		else {
		    return false;
		}
	}
	else if (var_right != 0) { // this is a variable
		if (left == 0) {
		    thisLeaf.number = 0;
			thisLeaf.variable = 0;
			thisLeaf.operand = NUMBER;						
		}
		else {
		    return false; // we can't simplify this expression
		}
	}
	
	else { // they are numbers			
		thisLeaf.number = left / right;
		thisLeaf.operand = NUMBER;
	}
	return true;
}

void Simplify::Sin() {

}

void Simplify::Cos() {

}
