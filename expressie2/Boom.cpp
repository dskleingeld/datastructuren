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

Boom::Boom(){
	root = new Leaf;
	currentLeaf = root;
	leafStack.push(root);
}

Boom::Leaf::Leaf(){
	branchLeft = NULL;
	branchRight = NULL;
}

Boom::~Boom(){
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
		switch(kar) {
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
				if (kar > 47 && kar < 58){//if the car is a ascii number
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
		number = std::atof(substring.c_str() );
	}
	else {
		switch (kar){
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
	if (operand == NUMBER || operand ==  VARIABLE || operand == PI) {
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

void Boom::Simplify() {
	Simp_inOrder(root);
}

void Boom::Evaluate(std::string variable, double value) {
	Eval_inOrder(root, variable[0], value); // Input value in x
	Simp_inOrder(root); // Simplify the expression
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
		if ((Temp->operand == COS)||(Temp->operand == SIN)) {
			display(Temp->operand, Temp);
			if(isUnaryOperator(Temp)) {			
				std::cout << "("; 
			}
			inOrder(Temp->branchLeft);
			inOrder(Temp->branchRight);
			if(isUnaryOperator(Temp)) {			
				std::cout << ")"; 
			}
		}
		else {	
			if(isOperator(Temp)) {			
				std::cout << "("; 
			}
			inOrder(Temp->branchLeft); 
			display(Temp->operand, Temp);//Entering second visit
			inOrder(Temp->branchRight);
			//At the end of inOrder, you are always at the third visit
			if(isOperator(Temp)) {			
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
	myfile.open ("graph.txt");
	myfile << "digraph G {\n";
	Graph_preOrder(root, myfile);
	myfile << "}";
	myfile.close();
}

void Boom::Simp_inOrder(Leaf* Temp) {
	// When you enter inOrder, you are always at the first visit
	if (Temp) {
		Simp_inOrder(Temp->branchLeft); 
		//Entering second visit
		Operate(Temp);
		Simp_inOrder(Temp->branchRight);
		//At the end of inOrder, you are always at the third visit
		std::cout << "Operand: " << Temp->operand << std::endl;
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

void Boom::Operate(Leaf* Temp) {
	if ((Temp->branchLeft != NULL) && (Temp->branchRight != NULL)) {
		left = 0;
		var_left = 0;
		right = 0;
		var_right = 0;
		switch (Temp->operand) {
		case PLUS:
			if (!FindElement(Temp->branchLeft, left, var_left) ||
				!FindElement(Temp->branchRight, right, var_right)) {
				// One of the children contains an operator
				break;
			}
			if (Plus(Temp)) { // Calculate summation
				Temp->branchLeft = NULL;
				Temp->branchRight = NULL;
			}
			break;
		case MINUS:
			if (!FindElement(Temp->branchLeft, left, var_left) ||
				!FindElement(Temp->branchRight, right, var_right)) {
				break;
			}
			if (Minus(Temp)) {
				Temp->branchLeft = NULL;
				Temp->branchRight = NULL;
				//TODO is this the right way to delete children?
			}
			break;
		case TIMES:
			if (!FindElement(Temp->branchLeft, left, var_left) ||
				!FindElement(Temp->branchRight, right, var_right)) {
				// One of the children contains an operator
				std::cout << "NAAA" << std::endl;
				break;
			}
			if (Times(Temp)) {
				Temp->branchLeft = NULL;
				Temp->branchRight = NULL;
			}
			break;
		case POWER:
			if (!FindElement(Temp->branchLeft, left, var_left) ||
				!FindElement(Temp->branchRight, right, var_right)) {
				break;
			}
			if (Power(Temp)) {
				Temp->branchLeft = NULL;
				Temp->branchRight = NULL;
			}
			break;
		case DEVIDE:
			if (!FindElement(Temp->branchLeft, left, var_left) ||
				!FindElement(Temp->branchRight, right, var_right)) {
				break;
			}
			if (Devide(Temp)) {
				Temp->branchLeft = NULL;
				Temp->branchRight = NULL;
				//TODO is this the right way to delete children?				
			}
			break;
		default:
			break;
		}
	}
	else if (Temp->branchLeft != NULL) {
		left = 0;
		var_left = 0;
		right = 0;
		var_right = 0;
		switch (Temp->operand) {
			case SIN:
				if (!FindElement(Temp->branchLeft, left, var_left)) {
					break;
				}
				if (Sin(Temp)) {
					Temp->branchLeft = NULL;
					Temp->branchRight = NULL;
				}
				break;
			case COS:
				if (!FindElement(Temp->branchLeft, left, var_left)) {
					break;
				}
				if (Cos(Temp)) {
					Temp->branchLeft = NULL;
					Temp->branchRight = NULL;
				}
				break;
			default:
				break;
		}
	}
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
		case TIMES:
			var = -1;
			break;
		default:
			return false;
			// TODO break;  ?
	}
	return true;
}

bool Boom::Plus(Leaf* thisLeaf) {
	if ((var_left != 0) && (var_right != 0)) { // x + y
		return false;
	}
	else if (var_left != 0) {
		if (isNearlyEqual(right, 0)) { // x + 0 = x
			thisLeaf->number = 0;
			thisLeaf->variable = var_left;
			thisLeaf->operand = VARIABLE;
		}
		else {
			return false;
		}
	}
	else if (var_right != 0) {
		if (isNearlyEqual(left, 0)) { // 0 + x = x
			thisLeaf->number = 0;
			thisLeaf->variable = var_right;
			thisLeaf->operand = VARIABLE;
		}
		else {
			return false;
		}
	}
	else { // a + b
		thisLeaf->number = left + right;
		thisLeaf->operand = NUMBER;
	}
	return true;
}

bool Boom::Minus(Leaf* thisLeaf) {
    if ((var_left != 0) && (var_right !=0)) { // both are variables
		if (var_right == var_left) { // x - x = 0
			thisLeaf->number = 0;
			thisLeaf->variable = 0;
			thisLeaf->operand = NUMBER;
		}
		else { // x - y
			return false; // we can't simplify this expression
		}		
	}
	else if (var_left != 0) { // this is a variable
		if (isNearlyEqual(right, 0)) { // x - 0 = x
		    thisLeaf->number = 0;
			thisLeaf->variable = var_left;
			thisLeaf->operand = VARIABLE;		
		}
		else { // x - a 
            return false; // we can't simplify this expression
		}
	}
	else if (var_right != 0) { // this is a variable
		// unable to simplify a - x further, since -x has to be written as: (-1) * x
		return false;
	}
	
	else { // they are numbers			
		thisLeaf->number = left - right;
		thisLeaf->operand = NUMBER;
	}
	return true;
}

bool Boom::Times(Leaf* thisLeaf) {
	if ((var_left != 0) && (var_right != 0)) { // x * y
		return false;
	}
	else if (var_left != 0){
		if (isNearlyEqual(right, 0)) { // x * 0 = 0
			thisLeaf->number = 0;
			thisLeaf->variable = 0;
			thisLeaf->operand = NUMBER;
		}
		else if (isNearlyEqual(right, 1)) { // x * 1 = x
			if (var_left != -1) {
				thisLeaf->number = 0;
				thisLeaf->variable = var_left;
				thisLeaf->operand = VARIABLE;
			}
			else {
				thisLeaf->branchRight == NULL;
				return false;
			}
		}
		else { // x * a
			return false;
		}
	}
	else if (var_right != 0) {
		if (isNearlyEqual(left, 0)) { // 0 * x = 0
			thisLeaf->number = 0;
			thisLeaf->variable = 0;
			thisLeaf->operand = NUMBER;
		}
		else if (isNearlyEqual(left, 1)) { // 1 * x = x
			thisLeaf->number = 0;
			thisLeaf->variable = var_right;
			thisLeaf->operand = VARIABLE;
		}
		else { // a * x
			return false;
		}
	}
	else { // a * b
		thisLeaf->number = left * right;
		thisLeaf->operand = NUMBER;
	}
	return true;
}

bool Boom::Power(Leaf* thisLeaf) {
	if ((var_left != 0) && (var_right != 0)) { // both are variables
		return false;
	}
	else if (var_left != 0) { // left is a variable
		if (isNearlyEqual(right, 1)) { // x ^ 1 = x
			thisLeaf->number = 0;
			thisLeaf->variable = var_left;
			thisLeaf->operand = VARIABLE;
		}
		else if (isNearlyEqual(right, 0)) { // x ^ 0 = 1
			thisLeaf->number = 1;
			thisLeaf->variable = 0;
			thisLeaf->operand = NUMBER;
		}
		else { // x ^ a 
			return false;
		}
	}
	else if (var_right != 0) { // right is a variable
		if (isNearlyEqual(left, 1)) { // 1 ^ x = 1
			thisLeaf->number = 1;
			thisLeaf->variable = 0;
			thisLeaf->operand = NUMBER;
		}
		else if (isNearlyEqual(left, 0)) { // 0 ^ x = 0
			thisLeaf->number = 0;
			thisLeaf->variable = 0;
			thisLeaf->operand = NUMBER;
		}
		else { // a ^ x
			return false;
		}
	}
	else { // a ^ b			
		thisLeaf->number = pow(left, right);
		thisLeaf->operand = NUMBER;
	}
	return true;
}

bool Boom::Devide(Leaf* thisLeaf) {
	if ((var_right == 0) && (isNearlyEqual(right, 0))) {
		std::cout << "Error. You are not allowed to devide by zero." << std::endl;
		return false;
	}
	else if ((var_left != 0) && (var_right !=0)) { // both are variables
		if (var_right == var_left) { // x / x
			thisLeaf->number = 1;
			thisLeaf->variable = 0;
			thisLeaf->operand = NUMBER;				
		}
		else { // x / y
            return false; // we can't simplify this expression
		}		
	}
	else if (var_left != 0) { // left is a variable
		if (isNearlyEqual(right, 1)) { // x / 1
		    thisLeaf->number = 0;
			thisLeaf->variable = var_left;
			thisLeaf->operand = VARIABLE;								
		}
		else { // x / a
		    return false;
		}
	}
	else if (var_right != 0) { // this is a variable
		if (isNearlyEqual(left, 0)) { // 0 / x
		    thisLeaf->number = 0;
			thisLeaf->variable = 0;
			thisLeaf->operand = NUMBER;						
		}
		else { // a / x
		    return false; // we can't simplify this expression
		}
	}
	
	else { // they are numbers			
		thisLeaf->number = left / right;
		thisLeaf->operand = NUMBER;
	}
	return true;
}

bool Boom::Sin(Leaf* thisLeaf) {
	if (var_left != 0) { // sin(x)
		return false;
	}
	thisLeaf->number = sin(left);
	thisLeaf->operand = NUMBER;
	return true;
}

bool Boom::Cos(Leaf* thisLeaf) {
	if (var_left != 0) { // sin(x)
		return false;
	}
	thisLeaf->number = cos(left);
	thisLeaf->operand = NUMBER;
	return true;
}

bool Boom::isNearlyEqual(double x, double y) {
	const double difference = 1e-5; // A small number
	return std::abs(x - y) <= difference;
}

// ---- Evaluate ----
void Boom::Eval_inOrder(Leaf* Temp, char variable, double value) {
	// When you enter inOrder, you are always at the first visit
	if (Temp) {
		if (Temp->variable == variable) {
			Temp->number = value;
			Temp->variable = 0;
			Temp->operand = NUMBER;
		}
		Eval_inOrder(Temp->branchLeft, variable, value);
		//Entering second visit
		Eval_inOrder(Temp->branchRight, variable, value);
		//At the end of inOrder, you are always at the third visit
	}
}

// ---- Differentiate ----

void Boom::diff(char toDiffTo){
	//add a new d/dx leaf at the top
	Leaf* newRoot;
	newRoot = new Leaf;
  
	newRoot->branchLeft = root;
	newRoot->operand = D;
	root = newRoot;
	
	diff_inOrder(toDiffTo, root);

	root = root->branchLeft; // we don't need d/dx entrance anymore
}

void Boom::diff_inOrder(char toDiffTo, Leaf* current) {
	//start a recursive differentiating function
	//walk until you find D
	if (current) {
		if (current->operand == D) {

			switch (current->branchLeft->operand) {
			case TIMES:
				productRule(toDiffTo, current->branchLeft);
				break;
			case PLUS:
				sumRule(toDiffTo, current->branchLeft);
				break;
			case MINUS:
				sumRule(toDiffTo, current->branchLeft);
				break;
			case DEVIDE:
				quotientRule(toDiffTo, current->branchLeft);
				break;
			case POWER:
				chainRule(toDiffTo, current->branchLeft);
				//TODO imprlement remaining cases
				//TODO start over from walk until you find D (recursie shit)
				break;
			case VARIABLE:
				variable(toDiffTo, current);
				break;
			case NUMBER:
				constant(toDiffTo, current);
			case COS:
				break;
			case SIN:
				break;
			default:
				break;
			}
			//current = current->branchLeft;
		}
		std::cout << "Operand is: " << current->operand << std::endl;
		diff_inOrder(toDiffTo, current->branchLeft);
		diff_inOrder(toDiffTo, current->branchRight);
	}
}

void Boom::variable(char toDiffTo, Leaf* current) {
	current->operand = NUMBER;
	current->number = 1;
	current->branchLeft = NULL;
	current->branchRight = NULL;
}

void Boom::constant(char toDiffTo, Leaf* current) {
	current->operand = NUMBER;
	current->number = 0;
	current->branchLeft = NULL;
	current->branchRight = NULL;
}

void Boom::quotientRule(char toDiffTo, Leaf* current){
  Leaf* f = current->branchLeft;
  Leaf* g = current->branchRight;
  
  Leaf* denominator = new Leaf; //noemer = denominator
  Leaf* numerator = new Leaf; //teller = numerator
  denominator->operand = POWER;
  numerator->operand = MINUS;

//  deepcopy(g, denominator->branchLeft);
  denominator->branchLeft = g;
  denominator->branchRight = new Leaf;
  denominator->branchRight->operand = NUMBER;
  denominator->branchRight->number = 2;
  
  Leaf* leftside = new Leaf;
  numerator->branchLeft = leftside;
  leftside->operand = TIMES;  
  leftside->branchLeft = g;
  leftside->branchRight = new Leaf;
  leftside->branchRight->operand = D;
//  leftside->branchRight->branchLeft = deepcopy(f);
//  deepcopy(f, leftside->branchRight->branchLeft);
  leftside->branchRight->branchLeft = f;

  Leaf* rightside = new Leaf;
  numerator->branchRight = rightside;
  rightside->operand = TIMES;
  rightside->branchLeft = f;
  rightside->branchRight = new Leaf;
  rightside->branchRight->operand = D;
  //rightside->branchRight->branchLeft = deepcopy(g)
  //deepcopy(g, rightside->branchRight->branchLeft);
  rightside->branchRight->branchLeft = g;
}

void Boom::sumRule(char toDiffTo, Leaf* current){
  Leaf* f = current->branchLeft;
  Leaf* g = current->branchRight;
  current->branchLeft = new Leaf;
  current->branchRight = new Leaf;
  current->branchLeft->operand = D;
  current->branchRight->operand = D;
  current->branchLeft->variable = toDiffTo; 
  current->branchRight->variable = toDiffTo; 
  current->branchLeft->branchLeft= f;
  current->branchRight->branchLeft= g;  
}
      
//called when multiplication is found, currentleaf points to multiplication
void Boom::productRule(char toDiffTo, Leaf* current){
  Leaf* g = current->branchLeft;
  Leaf* f = current->branchRight;
  Leaf* dg;
  Leaf* df;
  
  current->operand = PLUS;
  
  //create left side of plus sign, (d/dx(g) * f
  current->branchLeft = new Leaf;
  current->branchLeft->operand = TIMES; 
  current->branchLeft->variable = toDiffTo; 
  dg = new Leaf;
  dg->operand = D;
//  dg->branchLeft->deepcopy(g);
  //deepcopy(g, dg->branchLeft);
  dg->branchLeft = g;
  current->branchLeft->branchLeft = dg;
  current->branchLeft->branchRight = f;
  
  
  //create right side of plus sign, (d/dx(f) * g  
  current->branchRight = new Leaf;
  current->branchRight->operand = TIMES;
  current->branchRight->variable = toDiffTo; 
  df = new Leaf;
  df->operand = D;
  //df->branchLeft->deepcopy(f);
  //deepcopy(df->branchLeft, f);
  df->branchLeft = f;
  current->branchRight->branchLeft = df;
  current->branchRight->branchRight = g; 
}

void Boom::chainRule(char toDiffTo, Leaf* current) {
	Leaf* f = current->branchLeft;
	Leaf* g = current->branchRight;
	Leaf* diff_f;
	Leaf* df;
	Leaf* dg;

	current->operand = TIMES;

	//create left side, d(f * g)
	current->branchLeft = new Leaf;
	current->branchLeft->operand = TIMES;
	current->branchLeft->variable = toDiffTo;
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
	current->branchLeft->branchLeft = diff_f;
	current->branchLeft->branchRight = g;

	//create right side, df
	df = new Leaf;
	df->operand = D;
	df->branchLeft = f;
	current->branchRight = df;
}

//copies an element leaf except the pointers
void Boom::copyLeaf(Leaf* x, Leaf* y){
  y->operand = x->operand;
  if (x->operand == NUMBER){y->number = x->number;}
  if (x->operand == VARIABLE){y->variable = x->variable;}  
}

//recursively go through the tree
void Boom::recDeepcopy(Leaf* x, Leaf* y){
  if(x){ //check if not null pointer	
	  copyLeaf(x, y);
	  
	  if(x->branchLeft){ y->branchLeft = new Leaf; }
	  recDeepcopy(x->branchLeft, y->branchLeft); 
	  
	  if(x->branchRight){ y->branchRight = new Leaf; }	  
	  recDeepcopy(x->branchRight, y->branchRight);  
  }
}

//makes a new copy called y of subtree x
void Boom::deepcopy(Leaf* x, Leaf* y){
	recDeepcopy(x, y); //copy x to y
  //return y;
}