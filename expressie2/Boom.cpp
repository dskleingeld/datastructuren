/**
* Boom.cpp
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file Boom.h
* @date 12-11-2016
**/

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Boom.h"

Boom::Boom() {
	root = new Leaf;
	currentLeaf = root;
	leafStack.push(root);
}

Boom::Leaf::Leaf() {
	branchLeft = NULL;
	branchRight = NULL;
	operand = EMPTY;
}

Boom::~Boom() {
	clear(root);
}

void Boom::clear(Leaf* temp)
{
	if (temp->branchLeft != NULL)
		clear(temp->branchLeft);
	if (temp->branchRight != NULL)
		clear(temp->branchRight);
	delete temp;
	temp = NULL;
}

void Boom::processInput(std::string substring) {
	typeOfLeaf operand = PLUS; // Need to initialize this enum
	char variable = -1;
	double number = 0;

	char kar = substring[0];
	if (substring.length() == 1) {
		switch (kar) {
		case '+':
			operand = PLUS;
			break;
		case '-':
			operand = MINUS;
			break;
		case '*':
			operand = TIMES;
			break;
		case '^':
			operand = POWER;
			break;
		case '/':
			operand = DEVIDE;
			break;
		default:
			if (kar > 47 && kar < 58) {//if the car is a ascii number
				operand = NUMBER;
				number = std::atof(substring.c_str());
			}
			else {
				operand = VARIABLE;
				variable = kar;
			}
			break;
		}
	}
	else if (stringIsNumber(substring)) {
		operand = NUMBER;
		number = std::atof(substring.c_str());
	}
	else {
		switch (kar) {
		case 's':
			operand = SIN;
			break;
		case 'c':
			operand = COS;
			break;
		case 'p':
			operand = PI;
			break;
		default:
			std::cout << "YOU SILLY PERSON THIS IS NOT POSSIBLE!!!!!" << std::endl;
			break;
		}
	}
	//Add a leaf with pointers and such
	addLeaf(operand, variable, number);
}

bool Boom::stringIsNumber(std::string substring) {
	char kar;
	kar = substring[0];
	if ((kar > 47 && kar < 58) || kar == 45) {
		//ASCII value represents a number or minus sign
		return true;
	}
	else {
		return false;
	}
}

void Boom::nextFreeBranch() {
	//Important: check if leafStack is not empty
	while (!leafStack.empty() && (leafStack.top()->branchRight == NULL)) {
		leafStack.pop();
	}
	//Go to right child
	if (!leafStack.empty()) {
		currentLeaf = leafStack.top()->branchRight;
		leafStack.pop();
	}
}

void Boom::addLeaf(typeOfLeaf operand, char variable, double number) {

	currentLeaf->operand = operand;
	//Store the variable OR number in currentLeaf
	if (variable == -1) {
		currentLeaf->number = number;
	}
	else {
		currentLeaf->variable = variable;
	}
	//Determine how many children this node needs (0, 1 or 2)
	if (operand == NUMBER || operand == VARIABLE || operand == PI) {
		//0 children
		nextFreeBranch();//sets current leaf to the next free branch
	}
	else if (operand == SIN || operand == COS) {
		//1 child (left)
		currentLeaf->branchLeft = new Leaf;
		//Go to left child
		leafStack.push(currentLeaf);
		currentLeaf = currentLeaf->branchLeft;
	}
	else {
		//2 children
		currentLeaf->branchRight = new Leaf;
		currentLeaf->branchLeft = new Leaf;
		//Go to left child
		leafStack.push(currentLeaf);
		currentLeaf = currentLeaf->branchLeft;
	}
}

void Boom::view() {
	//Display the tree as a mathematical expression
	inOrder(root);
}

bool Boom::isOperator(Leaf* Temp) {
	if ((Temp->operand != PLUS) &&
		(Temp->operand != MINUS)) {
		return false;
	}
	return true;
}

bool Boom::isUnaryOperator(Leaf* Temp) {
	if ((Temp->operand != COS) &&
		(Temp->operand != SIN) &&
		(Temp->operand != POWER) &&
		(Temp->operand != D)) {
		return false;
	}
	return true;
}

void Boom::inOrder(Leaf* Temp) {
	//When you enter inOrder, you are always at the first visit
	if (Temp) {
		if ((Temp->operand == COS) || (Temp->operand == SIN) || (Temp->operand == D)) {
			display(Temp->operand, Temp);
			if (isUnaryOperator(Temp)) {
				std::cout << "(";
			}
			inOrder(Temp->branchLeft);
			inOrder(Temp->branchRight);
			if (isUnaryOperator(Temp)) {
				std::cout << ")";
			}
		}
		else {
			if (isOperator(Temp)) {
				std::cout << "(";
			}
			inOrder(Temp->branchLeft);
			display(Temp->operand, Temp);//Entering second visit
			inOrder(Temp->branchRight);
			//At the end of inOrder, you are always at the third visit
			if (isOperator(Temp)) {
				std::cout << ")";
			}
		}
	}
}

void Boom::display(typeOfLeaf operand, Leaf* Temp) {
	switch (operand) {
	case PLUS:
		std::cout << " + ";
		break;
	case MINUS:
		std::cout << " - ";
		break;
	case TIMES:
		std::cout << "*";
		break;
	case POWER:
		std::cout << "^";
		break;
	case DEVIDE:
		std::cout << " / ";
		break;
	case SIN:
		std::cout << "sin";
		break;
	case COS:
		std::cout << "cos";
		break;
	case PI:
		std::cout << "pi";
		break;
	case NUMBER:
		if (isNearlyEqual(Temp->number, 0)) {
			// Number is actually zero, but there is still a floating point difference
			Temp->number = 0;
		}
		std::cout << Temp->number;
		break;
	case VARIABLE:
		std::cout << Temp->variable;
		break;
	case D:
		std::cout << "d/dx";
		break;
	default:
		break;
	}
}

void Boom::writeLabel(typeOfLeaf operand, Leaf* Temp, std::ofstream & myfile) {
	myfile << "  " << counter << " ";
	switch (operand) {
	case PLUS:
		myfile << "[label=\"+\"]" << std::endl;
		break;
	case MINUS:
		myfile << "[label=\"-\"]" << std::endl;
		break;
	case TIMES:
		myfile << "[label=\"*\"]" << std::endl;
		break;
	case POWER:
		myfile << "[label=\"^\"]" << std::endl;
		break;
	case DEVIDE:
		myfile << "[label=\"/\"]" << std::endl;
		break;
	case SIN:
		myfile << "[label=\"sin\"]" << std::endl;
		break;
	case COS:
		myfile << "[label=\"cos\"]" << std::endl;
		break;
	case PI:
		myfile << "[label=\"pi\"]" << std::endl;
		break;
	case NUMBER:
		myfile << "[label=\"" << Temp->number << "\"]" << std::endl;
		break;
	case VARIABLE:
		myfile << "[label=\"" << Temp->variable << "\"]" << std::endl;
		break;
	case D:
		myfile << "[label=\"d/dx\"]" << std::endl;
	default:
		break;
	}
}

void Boom::writeConnection(std::ofstream & myfile, std::stack<int> myStack) {
	//Reverse the stack-order
	std::stack<int> anotherStack;
	if (!myStack.empty()) {
		anotherStack.push(myStack.top());
		myStack.pop();
	}
	if (!myStack.empty()) {
		//Only do this when stack contains 2 items or more
		myfile << "  ";
		anotherStack.push(myStack.top());
		myfile << anotherStack.top() << " -> ";
		anotherStack.pop();
		if (!anotherStack.empty()) {
			myfile << anotherStack.top() << std::endl;
		}
	}
}

void Boom::graph_preOrder(Leaf* Temp, std::ofstream & myfile) {
	if (Temp) {
		writeLabel(Temp->operand, Temp, myfile);
		Graph_Stack.push(counter);
		counter += 1;
		writeConnection(myfile, Graph_Stack);
		graph_preOrder(Temp->branchLeft, myfile);
		graph_preOrder(Temp->branchRight, myfile);
		if (!Graph_Stack.empty()) {
			Graph_Stack.pop();
		}
	}
}

void Boom::graph_dot(std::string filename) {
	counter = 1;
	std::ofstream myfile;
	myfile.open(filename);
	if (myfile.is_open()) {
		myfile << "digraph G {\n";
		graph_preOrder(root, myfile);
		myfile << "}";
		myfile.close();
	}
	else {
		std::cout << "Error: Could not open " << filename << "." << std::endl;
	}
}

// ---- Simplifiy ----
void Boom::simplify() {
	Leaf* previous = new Leaf;
	previous->branchLeft = root;

	simp_inOrder(root, previous, true);
	root = previous->branchLeft;
}

void Boom::simp_inOrder(Leaf* Temp, Leaf* previous, bool isLeft) {
	// When you enter inOrder, you are always at the first visit
	if (Temp) {
		simp_inOrder(Temp->branchLeft, Temp, true);
		//Entering second visit
		simp_inOrder(Temp->branchRight, Temp, false);
		//At the end of inOrder, you are always at the third visit
		operate(Temp, previous, isLeft);
	}
}

void Boom::operate(Leaf* current, Leaf* previous, bool isLeft) {
	if ((current->branchLeft != NULL) && (current->branchRight != NULL)) {
		left = 0;
		var_left = 0;
		right = 0;
		var_right = 0;
		
		/* Find values in left and right child of current operator */
		findElement(current->branchLeft, left, var_left);
		findElement(current->branchRight, right, var_right);

		/* The following if statements will check whether one of the children contains the number 0 or 1
		   and will execute the appropriate action */
		/* left = 0 */
		if ((current->branchRight->operand != NUMBER) && (current->branchLeft->operand == NUMBER) && isNearlyEqual(left, 0)) {
			if ((current->operand == TIMES) || (current->operand == DEVIDE) || 
				(current->operand == POWER)) {
				if (isLeft) {
					previous->branchLeft = setToZero();
				}
				else {
					previous->branchRight = setToZero();
				}
			}
			else if (current->operand == PLUS) {
				if (isLeft) {
					current = current->branchRight;
					previous->branchLeft = current;
				}
				else {
					current = current->branchRight;
					previous->branchRight = current;
				}
			}
		}
		/* right = 0 */
		else if ((current->branchLeft->operand != NUMBER) && (current->branchRight->operand == NUMBER) && isNearlyEqual(right, 0)) {
			if (current->operand == TIMES) {
				if (isLeft) {
					previous->branchLeft = setToZero();
				}
				else {
					previous->branchRight = setToZero();
				}
			}
			else if ((current->operand == PLUS) || (current->operand == MINUS)) {
				if (isLeft) {
					current = current->branchLeft;
					previous->branchLeft = current;
				}
				else {
					current = current->branchLeft;
					previous->branchRight = current;
				}
			}
			else if (current->operand == DEVIDE) {
				std::cout << "Division by zero is not allowed." << std::endl;
			}
			else if (current->operand == POWER) {
				if (isLeft) {
					previous->branchLeft = setToOne();
				}
				else {
					previous->branchRight = setToOne();
				}
			}
		}
		/* right = 1*/
		else if ((current->branchLeft->operand != NUMBER) && (current->branchRight->operand == NUMBER) && isNearlyEqual(right, 1)) {
			if ((current->operand == TIMES) || (current->operand == DEVIDE) || (current->operand == POWER)) {
				if (isLeft) {
					current = current->branchLeft;
					previous->branchLeft = current;
				}
				else {
					current = current->branchLeft;
					previous->branchRight = current;
				}
			}
		}
		/* left = 1 */
		else if ((current->branchRight->operand != NUMBER) && (current->branchLeft->operand == NUMBER) && isNearlyEqual(left, 1)) {
			if (current->operand == TIMES) {
				if (isLeft) {
					current = current->branchRight;
					previous->branchLeft = current;
				}
				else {
					current = current->branchRight;
					previous->branchRight = current;
				}
			}
			else if (current->operand == POWER) {
				if (isLeft) {
					previous->branchLeft = setToOne();
				}
				else {
					previous->branchRight = setToOne();
				}
			}
		}
		/* If no 1 or 0 was found, we will try to calculate the result as follows */
		else {
			// Check for 'deep summations', for example: (2 + x) + 4 = 6 + x
			bool deepsum_success = false;
			Leaf* temp = new Leaf;
			temp = deepSummation(current, deepsum_success);
			if (deepsum_success) {
				if (isLeft) {
					current = temp;
					previous->branchLeft = current;
				}
				else {
					current = temp;
					previous->branchRight = current;
				}
			}
			// TODO: do the same thing for 'deep multiplications' for example: 2*x * 3 = 6*x
			// if success is false, continue to the regular operations:
			if (!deepsum_success) {
				switch (current->operand) {
				case PLUS:
					if (plus(current)) {
						current->branchLeft = NULL;
						current->branchRight = NULL;
					}
					break;
				case MINUS:
					if (minus(current)) {
						current->branchLeft = NULL;
						current->branchRight = NULL;
						//TODO is this the right way to delete children?
					}
					break;
				case TIMES:
					if (times(current)) {
						current->branchLeft = NULL;
						current->branchRight = NULL;
					}
					break;
				case POWER:
					if (power(current)) {
						current->branchLeft = NULL;
						current->branchRight = NULL;
					}
					break;
				case DEVIDE:
					if (devide(current)) {
						current->branchLeft = NULL;
						current->branchRight = NULL;
					}
					break;
				default:
					break;
				}
			}
		}
	}
	/* If all else fails, it might be sin or cos */
	else if (current->branchLeft != NULL) {
		left = 0;
		var_left = 0;
		right = 0;
		var_right = 0;
		switch (current->operand) {
		case SIN:
			if (!findElement(current->branchLeft, left, var_left)) {
				break;
			}
			if (sinus(current)) {
				current->branchLeft = NULL;
				current->branchRight = NULL;
			}
			break;
		case COS:
			if (!findElement(current->branchLeft, left, var_left)) {
				break;
			}
			if (cosinus(current)) {
				current->branchLeft = NULL;
				current->branchRight = NULL;
			}
			break;
		default:
			break;
		}
	}
}

int Boom::calc_sum(Leaf* a, typeOfLeaf a_operand, Leaf* b, typeOfLeaf b_operand) {
	int c, d;
	if (a_operand == MINUS) {
		c = -1 * a->number;
	}
	else {
		c = a->number;
	}
	if (b_operand == MINUS) {
		d = -1 * b->number;
	}
	else {
		d = b->number;
	}
	return c + d;
}

Boom::Leaf* Boom::deepSummation(Leaf* current, bool& success) {
	if ((current->branchLeft->operand == NUMBER) && ((current->branchRight->operand == PLUS) || (current->branchRight->operand == MINUS))) {
		double total;
		if (current->branchRight->branchLeft->operand == NUMBER) {
			// number + (number + x)
			total = calc_sum(current->branchRight->branchLeft, current->operand, current->branchLeft, PLUS); //left side always +
			current = current->branchRight;
			current->branchLeft->number = total;
			success = true;
			return current;
		}
		else if (current->branchRight->branchRight->operand == NUMBER) {
			// number + ( x + number )
			total = calc_sum(current->branchRight->branchRight, current->branchRight->operand, current->branchLeft, PLUS);
			current = current->branchRight;
			current->branchRight->number = total;
			success = true;
			return current;
		}
	}
	else if ((current->branchRight->operand == NUMBER) && ((current->branchLeft->operand == PLUS) || (current->branchLeft->operand == MINUS))) {
		double total;
		if (current->branchLeft->branchLeft->operand == NUMBER) {
			// (number + x) + number
			total = calc_sum(current->branchLeft->branchLeft, PLUS, current->branchRight, current->operand);
			current = current->branchLeft;
			current->branchLeft->number = total;
			success = true;
			return current;
		}
		else if (current->branchLeft->branchRight->operand == NUMBER) {
			// ( x + number ) + number
			total = calc_sum(current->branchLeft->branchRight, current->branchLeft->operand, current->branchRight, current->operand);
			current = current->branchLeft;
			current->branchRight->number = total;
			success = true;
			return current;
		}
	}
	success = false;
	return current;
}

bool Boom::plus(Leaf* thisLeaf) {
	if ((thisLeaf->branchLeft->operand == NUMBER) && (thisLeaf->branchRight->operand == NUMBER)) {
		thisLeaf->number = left + right;
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

bool Boom::minus(Leaf* thisLeaf) {
	if ((var_left != 0) && (var_right != 0)) { // both are variables
		if (var_right == var_left) { // x - x = 0
			thisLeaf->number = 0;
			thisLeaf->variable = 0;
			thisLeaf->operand = NUMBER;
			return true;
		}
	}
	if ((thisLeaf->branchLeft->operand == NUMBER) && (thisLeaf->branchRight->operand == NUMBER)) {
		thisLeaf->number = left - right;
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

bool Boom::times(Leaf* thisLeaf) {
	if ((thisLeaf->branchLeft->operand == NUMBER) && (thisLeaf->branchRight->operand == NUMBER)) {
		thisLeaf->number = left * right;
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

bool Boom::power(Leaf* thisLeaf) {
	if ((thisLeaf->branchLeft->operand == NUMBER) && (thisLeaf->branchRight->operand == NUMBER)) {
		thisLeaf->number = pow(left, right);
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

bool Boom::devide(Leaf* thisLeaf) {
	if ((var_right == 0) && (isNearlyEqual(right, 0))) {
		std::cout << "Error: Unable to devide by zero." << std::endl;
	}
	if ((thisLeaf->branchLeft->operand == NUMBER) && (thisLeaf->branchRight->operand == NUMBER)) {
		thisLeaf->number = left / right;
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

bool Boom::sinus(Leaf* thisLeaf) {
	if (thisLeaf->branchLeft->operand == NUMBER) {
		thisLeaf->number = sin(left);
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

bool Boom::cosinus(Leaf* thisLeaf) {
	if (thisLeaf->branchLeft->operand == NUMBER) {
		thisLeaf->number = cos(left);
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

// ---- Evaluate ----
void Boom::evaluate(std::string variable, double value) {
	Leaf* newRoot;
	newRoot = new Leaf;
	newRoot->branchLeft = root;
	eval_inOrder(root, variable[0], value); // Input value in x
	simp_inOrder(root, newRoot, true); // Simplify the expression
}

void Boom::eval_inOrder(Leaf* temp, char variable, double value) {
	// When you enter inOrder, you are always at the first visit
	if (temp) {
		if (temp->variable == variable) {
			temp->number = value;
			temp->variable = 0;
			temp->operand = NUMBER;
		}
		eval_inOrder(temp->branchLeft, variable, value);
		//Entering second visit
		eval_inOrder(temp->branchRight, variable, value);
		//At the end of inOrder, you are always at the third visit
	}
}

// ---- Differentiate ----
void Boom::differentiate(char toDiffTo) {
	/* Add a new d/dx leaf at the top */
	Leaf* newRoot;
	newRoot = new Leaf;

	newRoot->branchLeft = root;
	newRoot->operand = D;
	
	Leaf* previous = new Leaf;
	previous->branchLeft = newRoot;
	
	diff_inOrder(toDiffTo, newRoot, previous, true);

	/* Set root to the appropriate leaf */
	root = previous;
	while (root->operand == EMPTY) {
		/* Delete root if it is empty */
		Leaf* temp = root;
		root = root->branchLeft;
		delete temp;
	}
}

void Boom::diff_inOrder(char toDiffTo, Leaf* current, Leaf* previous, bool left) {
	//start a recursive differentiating function
	//walk until you find D
	if (current) {
		if (current->operand == D) {
			switch (current->branchLeft->operand) {
			case TIMES:
				current = productRule(toDiffTo, current, previous);
				if (left) {
					previous->branchLeft = current;
				}
				else {
					previous->branchRight = current;
				}
				break;
			case PLUS:
				current = sumRule(toDiffTo, current, previous);
				if (left) {
					previous->branchLeft = current;
				}
				else {
					previous->branchRight = current;
				}
				break;
			case MINUS:
				current = sumRule(toDiffTo, current, previous);
				if (left) {
					previous->branchLeft = current;
				}
				else {
					previous->branchRight = current;
				}
				break;
			case DEVIDE:
				current = quotientRule(toDiffTo, current, previous);
				if (left) {
					previous->branchLeft = current;
				}
				else {
					previous->branchRight = current;
				}
				break;
			case POWER:
				current = powerRule(toDiffTo, current, previous);
				if (left) {
					previous->branchLeft = current;
				}
				else {
					previous->branchRight = current;
				}
				break;
			case VARIABLE:
				current = variable(toDiffTo, current, previous);
				if (left) {
					previous->branchLeft = current;
				}
				else {
					previous->branchRight = current;
				}
				break;
			case NUMBER:
				current = constant(toDiffTo, current, previous);
				if (left) {
					previous->branchLeft = current;
				}
				else {
					previous->branchRight = current;
				}
				break;
			case COS:
				current = cosRule(toDiffTo, current, previous);
				if (left) {
					previous->branchLeft = current;
				}
				else {
					previous->branchRight = current;
				}
				break;
			case SIN:
				current = sinRule(toDiffTo, current, previous);
				if (left) {
					previous->branchLeft = current;
				}
				else {
					previous->branchRight = current;
				}
				break;
			default:
				std::cout << "Error: Something went quite wrong. Our sincere apologies";
				break;
			}
		}
		diff_inOrder(toDiffTo, current->branchLeft, current, true);
		diff_inOrder(toDiffTo, current->branchRight, current, false);
	}
}

Boom::Leaf* Boom::cosRule(char toDiffTo, Leaf* current, Leaf* previous) {
	/* Create new, empty leaf to generate our new subtree */
	Leaf* temp = new Leaf;
	temp->branchLeft = new Leaf;
	Leaf* f = current->branchLeft->branchLeft; //func in the cos

	/* Chain rule */
	temp->operand = TIMES;

	Leaf* right = new Leaf;
	temp->branchRight = right;

	right->operand = TIMES;
	right->branchLeft = new Leaf;
	right->branchLeft->operand = D;
	right->branchLeft->branchLeft = deepcopy(f);

	right->branchRight = new Leaf;
	right->branchRight->operand = NUMBER;
	right->branchRight->number = -1;

	temp->branchLeft->operand = SIN;
	temp->branchLeft->branchLeft = deepcopy(f);

	/* Return the subtree */
	return temp;
}

Boom::Leaf* Boom::sinRule(char toDiffTo, Leaf* current, Leaf* previous) {
	Leaf* temp = new Leaf;
	temp->branchLeft = new Leaf;
	Leaf* f = current->branchLeft->branchLeft;

	temp->operand = TIMES;
	temp->branchRight = new Leaf;
	temp->branchRight->operand = D; //chainrule part
	temp->branchRight->branchLeft = deepcopy(f);

	temp->branchLeft->operand = COS;
	temp->branchLeft->branchLeft = deepcopy(f);

	return temp;
}

Boom::Leaf* Boom::variable(char toDiffTo, Leaf* current, Leaf* previous) {
	/* Check if the variable is x or y, TODO: check this earlier? */
	bool found_var = false;
	contains_var(current->branchLeft, found_var, toDiffTo);
	if (found_var) {
		//if (current->branchLeft->variable == toDiffTo) {
		Leaf* temp = new Leaf;
		temp->operand = NUMBER;
		temp->number = 1;
		return temp;
	}
	else {
		Leaf* temp = new Leaf;
		temp->operand = VARIABLE;
		temp->variable = current->branchLeft->variable;
		return temp;
	}
}

Boom::Leaf* Boom::constant(char toDiffTo, Leaf* current, Leaf* previous) {
	Leaf* Temp = new Leaf;
	Temp->operand = NUMBER;
	Temp->number = 0;

	return Temp;
}

Boom::Leaf* Boom::sumRule(char toDiffTo, Leaf* current, Leaf* previous) {

	Leaf* temp = new Leaf; 
	
	/* Check if we indeed have an x on one or both sides */
	bool found_var_left = false;
	bool found_var_right = false;
	contains_var(current->branchLeft->branchLeft, found_var_left, toDiffTo);
	contains_var(current->branchLeft->branchRight, found_var_right, toDiffTo);
	if ((!found_var_left) && (!found_var_right)) {
		temp = setToZero();
		return temp;
	}

	temp->operand = current->branchLeft->operand;
	
	Leaf* f = current->branchLeft->branchLeft;
	Leaf* g = current->branchLeft->branchRight;
	temp->branchLeft = new Leaf;
	temp->branchRight = new Leaf;
	temp->branchLeft->operand = D;
	temp->branchRight->operand = D;
	temp->branchLeft->variable = toDiffTo;
	temp->branchRight->variable = toDiffTo;
	temp->branchLeft->branchLeft = f;
	temp->branchRight->branchLeft = g;

	return temp;
}

Boom::Leaf* Boom::quotientRule(char toDiffTo, Leaf* current, Leaf* previous) {
	Leaf* temp = new Leaf;

	/* Check if we indeed have an x on one or both sides */
	bool found_var_left = false;
	bool found_var_right = false;
	contains_var(current->branchLeft->branchLeft, found_var_left, toDiffTo);
	contains_var(current->branchLeft->branchRight, found_var_right, toDiffTo);
	if ((!found_var_left) && (!found_var_right)) {
		temp = setToZero();
		return temp;
	}

	temp->operand = DEVIDE;

	Leaf* f = current->branchLeft->branchLeft;
	Leaf* g = current->branchLeft->branchRight;

	Leaf* denominator = new Leaf; //noemer = denominator
	Leaf* numerator = new Leaf; //teller = numerator
	denominator->operand = POWER;
	numerator->operand = MINUS;

	denominator->branchLeft = deepcopy(g);
	denominator->branchRight = new Leaf;
	denominator->branchRight->operand = NUMBER;
	denominator->branchRight->number = 2;

	Leaf* leftside = new Leaf;
	numerator->branchLeft = leftside;
	leftside->operand = TIMES;
	leftside->branchLeft = g;
	leftside->branchRight = new Leaf;
	leftside->branchRight->operand = D;
	leftside->branchRight->branchLeft = deepcopy(f);
	leftside->branchRight->branchLeft = f;

	Leaf* rightside = new Leaf;
	numerator->branchRight = rightside;
	rightside->operand = TIMES;
	rightside->branchLeft = f;
	rightside->branchRight = new Leaf;
	rightside->branchRight->operand = D;
	rightside->branchRight->branchLeft = deepcopy(g);
	rightside->branchRight->branchLeft = g;
	
	temp->branchLeft = numerator;
	temp->branchRight = denominator;
	return temp;
}

//called when multiplication is found, currentleaf points to multiplication
Boom::Leaf* Boom::productRule(char toDiffTo, Leaf* current, Leaf* previous) {
	Leaf* temp = new Leaf;

	/* Check if we indeed have an x on one or both sides */
	bool found_var_left = false;
	bool found_var_right = false;
	contains_var(current->branchLeft->branchLeft, found_var_left, toDiffTo);
	contains_var(current->branchLeft->branchRight, found_var_right, toDiffTo);
	if ((!found_var_left) && (!found_var_right)) {
		temp = setToZero();
		return temp;
	}

	Leaf* g = current->branchLeft->branchLeft;
	Leaf* f = current->branchLeft->branchRight;
	Leaf* dg;
	Leaf* df;
	
	temp->operand = PLUS;

	//create left side of plus sign, (d/dx(g) * f
	temp->branchLeft = new Leaf;
	temp->branchLeft->operand = TIMES;
	//temp->branchLeft->variable = toDiffTo;
	dg = new Leaf;
	dg->operand = D;
	dg->branchLeft = deepcopy(g);
	temp->branchLeft->branchLeft = dg;
	temp->branchLeft->branchRight = f;

	//create right side of plus sign, (d/dx(f) * g  
	temp->branchRight = new Leaf;
	temp->branchRight->operand = TIMES;
	//temp->branchRight->variable = toDiffTo;
	df = new Leaf;
	df->operand = D;
	df->branchLeft = deepcopy(f);
	temp->branchRight->branchLeft = df;
	temp->branchRight->branchRight = g;

	return temp;
}

Boom::Leaf* Boom::powerRule(char toDiffTo, Leaf* current, Leaf* previous) {
	Leaf* temp = new Leaf;

	/* Check if we indeed have an x on one or both sides */
	bool found_var_left = false;
	bool found_var_right = false;
	contains_var(current->branchLeft->branchLeft, found_var_left, toDiffTo);
	contains_var(current->branchLeft->branchRight, found_var_right, toDiffTo);
	if ((!found_var_left) && (!found_var_right)) {
		temp = setToZero();
		return temp;
	}
	if (found_var_right) { // a ^ x
		std::cout << "Error: Unable to differentiate equations of the form [a ^ f(x)]" << std::endl;
		temp = current; // keep d/dx in the tree
		return temp;
	}

	Leaf* f = current->branchLeft->branchLeft;
	Leaf* g = current->branchLeft->branchRight;
	Leaf* diff_f;
	Leaf* df;
	Leaf* dg;

	temp->operand = TIMES;

	//create left side, d(f * g)
	temp->branchLeft = new Leaf;
	temp->branchLeft->operand = TIMES;
	//temp->branchLeft->variable = toDiffTo;
	diff_f = new Leaf;
	diff_f->operand = POWER;
	diff_f->branchLeft = f;
	dg = new Leaf;
	dg->operand = MINUS;
	dg->branchLeft = g;
	dg->branchRight = new Leaf;
	dg->branchRight->operand = NUMBER;
	dg->branchRight->number = 1;
	diff_f->branchRight = dg;
	temp->branchLeft->branchLeft = diff_f;
	temp->branchLeft->branchRight = g;

	//create right side, df
	df = new Leaf;
	df->operand = D;
	df->branchLeft = deepcopy(f);
	temp->branchRight = df;

	return temp;
}

//copies an element leaf except the pointers
void Boom::copyLeaf(Leaf* x, Leaf* y) {
	y->operand = x->operand;
	if (x->operand == NUMBER) { y->number = x->number; }
	if (x->operand == VARIABLE) { y->variable = x->variable; }
}

//recursively go through the tree
void Boom::recDeepcopy(Leaf* x, Leaf* y) {
	if (x) { //check if not null pointer	
		copyLeaf(x, y);

		if (x->branchLeft) { y->branchLeft = new Leaf; }
		recDeepcopy(x->branchLeft, y->branchLeft);

		if (x->branchRight) { y->branchRight = new Leaf; }
		recDeepcopy(x->branchRight, y->branchRight);
	}
}

//makes a new copy called y of subtree x
Boom::Leaf* Boom::deepcopy(Leaf* x) {
	Leaf* y = new Leaf;
	recDeepcopy(x, y); //copy x to y
	return y;
}

void Boom::contains_var(Leaf* current, bool& found_var, char toDiffTo) {
	if (current) {
		contains_var(current->branchLeft, found_var, toDiffTo);
		contains_var(current->branchRight, found_var, toDiffTo);
		if (current->variable == toDiffTo) {
			found_var = true;
		}
	}
}

bool Boom::isNearlyEqual(double x, double y) {
	const double difference = 1e-5; // A small number
	return std::abs(x - y) <= difference;
}

Boom::Leaf* Boom::setToZero() {
	Leaf* temp = new Leaf;
	temp->number = 0;
	temp->variable = 0;
	temp->operand = NUMBER;
	return temp;
}

Boom::Leaf* Boom::setToOne() {
	Leaf* temp = new Leaf;
	temp->number = 1;
	temp->variable = 0;
	temp->operand = NUMBER;
	return temp;
}

bool Boom::findElement(Leaf* currentLeaf, double &num, char &var) {
	switch (currentLeaf->operand) {
	case PI:
		num = 3.14159265359;
		currentLeaf->number = num;
		currentLeaf->operand = NUMBER;
		break;
	case VARIABLE:
		var = currentLeaf->variable;
		break;
	case NUMBER:
		num = currentLeaf->number;
		break;
	default:
		return false;
	}
	return true;
}