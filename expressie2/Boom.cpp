/**
* Boom.cpp
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file Boom.h
* @date 12-10-2016
**/

// TODO: Nu kijken we of iets gelijk is aan nul door te vergelijken met = 0
// maar een double kan ook net-niet-helemaal 0 zijn,
// dus we moeten eigenlijk vergelijken met < 0.0001 ofzo...

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
}

Boom::~Boom() {
	Clear(root);
}

void Boom::Clear(Leaf* Temp)
{
	if (Temp->branchLeft != NULL)
		Clear(Temp->branchLeft);
	if (Temp->branchRight != NULL)
		Clear(Temp->branchRight);
	delete Temp;
	Temp = NULL;
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
	//Display the tree graphically
	Graph_display();
}

void Boom::Evaluate(std::string variable, double value) {
	Leaf* newRoot;
	newRoot = new Leaf;
	newRoot->branchLeft = root;
	Eval_inOrder(root, variable[0], value); // Input value in x
	Simp_inOrder(root, newRoot, true); // Simplify the expression
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
		(Temp->operand != POWER)) {
		return false;
	}
	return true;
}

void Boom::inOrder(Leaf* Temp) {
	//When you enter inOrder, you are always at the first visit
	if (Temp) {
		if ((Temp->operand == COS) || (Temp->operand == SIN)) {
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

void Boom::Graph_preOrder(Leaf* Temp, std::ofstream & myfile) {
	if (Temp) {
		writeLabel(Temp->operand, Temp, myfile);
		Graph_Stack.push(counter);
		counter += 1;
		writeConnection(myfile, Graph_Stack);
		Graph_preOrder(Temp->branchLeft, myfile);
		Graph_preOrder(Temp->branchRight, myfile);
		if (!Graph_Stack.empty()) {
			Graph_Stack.pop();
		}
	}
}

void Boom::Graph_display() {
	counter = 1;
	std::ofstream myfile;
	myfile.open("graph.txt");
	myfile << "digraph G {\n";
	Graph_preOrder(root, myfile);
	myfile << "}";
	myfile.close();
}

// ---- Simplifiy ----

void Boom::Simplify() {
	Leaf* previous = new Leaf;
	previous->branchLeft = root;

	Simp_inOrder(root, previous, true);
	root = previous->branchLeft;
}

void Boom::Simp_inOrder(Leaf* Temp, Leaf* previous, bool isLeft) {
	// When you enter inOrder, you are always at the first visit
	if (Temp) {
		Simp_inOrder(Temp->branchLeft, Temp, true);
		//Entering second visit
		Simp_inOrder(Temp->branchRight, Temp, false);
		//At the end of inOrder, you are always at the third visit
		Operate(Temp, previous, isLeft);
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

void Boom::Operate(Leaf* current, Leaf* previous, bool isLeft) {
	if ((current->branchLeft != NULL) && (current->branchRight != NULL)) {
		left = 0;
		var_left = 0;
		right = 0;
		var_right = 0;
		
		/* Find values in left and right child of current operator */
		FindElement(current->branchLeft, left, var_left);
		FindElement(current->branchRight, right, var_right);

		/* The following if statements will check whether one of the children contains the number 0 or 1
		   and will execute the appropriate action */
		/* left = 0 */
		if ((current->branchRight->operand != NUMBER) && (current->branchLeft->operand == NUMBER) && isNearlyEqual(left, 0)) {
			if ((current->operand == TIMES) || (current->operand == DEVIDE) || 
				(current->operand == POWER)) {
				if (isLeft) {
					previous->branchLeft = SetToZero();
				}
				else {
					previous->branchRight = SetToZero();
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
					previous->branchLeft = SetToZero();
				}
				else {
					previous->branchRight = SetToZero();
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
					previous->branchLeft = SetToOne();
				}
				else {
					previous->branchRight = SetToOne();
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
				if (left) {
					previous->branchLeft = SetToOne();
				}
				else {
					previous->branchRight = SetToOne();
				}
			}
		}
		/* If no 1 or 0 was found, we will try to calculate the result as follows */
		else {
			switch (current->operand) {
			case PLUS:
				if (Plus(current)) {
					current->branchLeft = NULL;
					current->branchRight = NULL;
				}
				break;
			case MINUS:
				if (Minus(current)) {
					current->branchLeft = NULL;
					current->branchRight = NULL;
					//TODO is this the right way to delete children?
				}
				break;
			case TIMES:
				if (Times(current)) {
					current->branchLeft = NULL;
					current->branchRight = NULL;
				}
				break;
			case POWER:
				if (Power(current)) {
					current->branchLeft = NULL;
					current->branchRight = NULL;
				}
				break;
			case DEVIDE:
				if (Devide(current)) {
					current->branchLeft = NULL;
					current->branchRight = NULL;			
				}
				break;
			default:
				break;
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
			if (!FindElement(current->branchLeft, left, var_left)) {
				break;
			}
			if (Sin(current)) {
				current->branchLeft = NULL;
				current->branchRight = NULL;
			}
			break;
		case COS:
			if (!FindElement(current->branchLeft, left, var_left)) {
				break;
			}
			if (Cos(current)) {
				current->branchLeft = NULL;
				current->branchRight = NULL;
			}
			break;
		default:
			break;
		}
	}
}

Boom::Leaf* Boom::SetToZero() {
	Leaf* temp = new Leaf;
	temp->number = 0;
	temp->variable = 0;
	temp->operand = NUMBER;
	return temp;
}

Boom::Leaf* Boom::SetToOne() {
	Leaf* temp = new Leaf;
	temp->number = 1;
	temp->variable = 0;
	temp->operand = NUMBER;
	return temp;
}

bool Boom::FindElement(Leaf* currentLeaf, double &num, char &var) {
	switch (currentLeaf->operand) {
	case PI:
		num = 3.14159265359;
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

bool Boom::Plus(Leaf* thisLeaf) {
	if ((thisLeaf->branchLeft->operand == NUMBER) && (thisLeaf->branchRight->operand == NUMBER)) {
		thisLeaf->number = left + right;
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

bool Boom::Minus(Leaf* thisLeaf) {
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

bool Boom::Times(Leaf* thisLeaf) {
	if ((thisLeaf->branchLeft->operand == NUMBER) && (thisLeaf->branchRight->operand == NUMBER)) {
		thisLeaf->number = left * right;
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

bool Boom::Power(Leaf* thisLeaf) {
	if ((thisLeaf->branchLeft->operand == NUMBER) && (thisLeaf->branchRight->operand == NUMBER)) {
		thisLeaf->number = pow(left, right);
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

bool Boom::Devide(Leaf* thisLeaf) {
	if ((var_right == 0) && (isNearlyEqual(right, 0))) {
		std::cout << "Error. You are not allowed to devide by zero." << std::endl;
	}
	if ((thisLeaf->branchLeft->operand == NUMBER) && (thisLeaf->branchRight->operand == NUMBER)) {
		thisLeaf->number = left / right;
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

bool Boom::Sin(Leaf* thisLeaf) {
	if (thisLeaf->branchLeft->operand == NUMBER) {
		thisLeaf->number = sin(left);
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

bool Boom::Cos(Leaf* thisLeaf) {
	if (thisLeaf->branchLeft->operand == NUMBER) {
		thisLeaf->number = cos(left);
		thisLeaf->operand = NUMBER;
		return true;
	}
	return false;
}

bool Boom::isNearlyEqual(double x, double y) {
	const double difference = 1e-5; // A small number
	return std::abs(x - y) <= difference;
}

// ---- Evaluate ----
void Boom::Eval_inOrder(Leaf* temp, char variable, double value) {
	// When you enter inOrder, you are always at the first visit
	if (temp) {
		if (temp->variable == variable) {
			temp->number = value;
			temp->variable = 0;
			temp->operand = NUMBER;
		}
		Eval_inOrder(temp->branchLeft, variable, value);
		//Entering second visit
		Eval_inOrder(temp->branchRight, variable, value);
		//At the end of inOrder, you are always at the third visit
	}
}

// ---- Differentiate ----

void Boom::diff(char toDiffTo) {
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
				current = powerRule(toDiffTo, current, previous);//FIXME
				if (left) {
					previous->branchLeft = current;
				}
				else {
					previous->branchRight = current;
				}
				break;
			case VARIABLE:
				current = variable(toDiffTo, current, previous);//FIXME
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
				std::cout << "HELLLUPP DIT KAN NIET WTF";
				break;
			}
		}
		diff_inOrder(toDiffTo, current->branchLeft, current, true);
		diff_inOrder(toDiffTo, current->branchRight, current, false);
	}
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
	contains_var(current->branchLeft, found_var_left, toDiffTo);
	contains_var(current->branchLeft, found_var_right, toDiffTo);
	if ((!found_var_left) && (!found_var_right)) {
		temp = SetToZero();
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
	contains_var(current->branchLeft, found_var_left, toDiffTo);
	contains_var(current->branchLeft, found_var_right, toDiffTo);
	if ((!found_var_left) && (!found_var_right)) {
		temp = SetToZero();
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
	contains_var(current->branchLeft, found_var_left, toDiffTo);
	contains_var(current->branchLeft, found_var_right, toDiffTo);
	if ((!found_var_left) && (!found_var_right)) {
		temp = SetToZero();
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
	contains_var(current->branchLeft, found_var_left, toDiffTo);
	contains_var(current->branchLeft, found_var_right, toDiffTo);
	if ((!found_var_left) && (!found_var_right)) {
		temp = SetToZero();
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


void Boom::deleteTopD(Leaf*& current) {
	Leaf* temp;

	//remove the top D
	temp = current;
	current = current->branchLeft;
	delete temp;
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
