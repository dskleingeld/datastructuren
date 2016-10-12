#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
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
	bool visit1 = false;
	bool visit3 = false;
	//Display the tree as a mathematical expression
	inOrder(root, visit1, visit3);
	//Display the tree graphically
	Graph_display();
}
/*
void Boom::preOrder(Leaf* Temp) {
	if (Temp) {
		if ((currentLeaf->operand == PLUS) ||
			(currentLeaf->operand == MINUS)) {
			inOrder(Temp->branchLeft);
			display(Temp->operand, Temp);
			inOrder(Temp->branchRight);
		}
		else if	
			((currentLeaf->operand == TIMES) ||
			(currentLeaf->operand == DEVIDE) ||
			(currentLeaf->operand == POWER)) {
			//Binary operator, needs in-order traversion
			std::cout << "(";
			inOrder(Temp->branchLeft);
			display(Temp->operand, Temp);
			inOrder(Temp->branchRight);
			std::cout << ")";
		}
		else {
			display(Temp->operand, Temp);
			preOrder(Temp->branchLeft);
			preOrder(Temp->branchRight);
		}
	}
}
*/

bool Boom::isNotOperator(Leaf* Temp) {
	if ((Temp->operand != PLUS) && 
			(Temp->operand != MINUS) &&
			(Temp->operand != POWER)) {
		return true;
	}
	return false;
}

void Boom::inOrder(Leaf* Temp, bool visit1, bool visit3) {
	if (Temp) {
		if ((Temp->operand == COS)||(Temp->operand == SIN)) {
			display(Temp->operand, Temp);
			inOrder(Temp->branchLeft, visit1, visit3);
			inOrder(Temp->branchRight, visit1, visit3);
		}
		else {	
			if(!isNotOperator(Temp)) {			
				std::cout << "(";
			}
			inOrder(Temp->branchLeft, visit1, visit3);
			display(Temp->operand, Temp);
			inOrder(Temp->branchRight, visit1, visit3);
			if(!isNotOperator(Temp)) {			
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
				std::cout << Temp->number;
				break;
			case VARIABLE:
				std::cout << Temp->variable;
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

