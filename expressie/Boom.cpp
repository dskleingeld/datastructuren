#include <string>
#include <cstdlib>
#include <iostream>
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

void Boom::processInput(std::string substring) {
	typeOfLeaf operand;
	char variable = -1;
	double number;

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
					number = (double)(kar-48);//-48 to go to normal numbers from ascii
				}
				else{ operand = VARIABLE; }
					variable = kar;
				break;
		}
	}
	else if (stringIsNumber(substring)) {
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
	while (leafStack.top()->branchRight == NULL) {
		leafStack.pop();
	}
	//Go to right child
	currentLeaf = leafStack.top()->branchRight;
	leafStack.pop();
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

void Boom::walkInorder() {
	while (currentLeaf->branchLeft != NULL) { //there is a left child
		std::cout << "Go to left" << std::endl;
		display(currentLeaf->operand);
		currentLeaf = currentLeaf->branchLeft; //go to left child
		leafStack.push(currentLeaf);
	}
	while (leafStack.top()->branchRight == NULL) { //find next right child
		std::cout << "Go up, looking for right child" << std::endl;
		display(currentLeaf->operand);
		leafStack.pop();	
	}
	currentLeaf = leafStack.top()->branchRight;
	std::cout << "Go to right" << std::endl;
	display(currentLeaf->operand);

	if (!leafStack.empty()) {
		leafStack.pop();	
		walkInorder(); //recursion
	}
	std::cout << "Stack is empty" << std::endl;
	return;
}

void Boom::display(typeOfLeaf operand) {
	switch (operand) {
			case PLUS:
				std::cout << "  +";
				break;
			case MINUS:
				std::cout << "  -";
				break;
			case TIMES:
				std::cout << "  *";
				break;			
			case POWER:
				std::cout << "  ^";
				break;				
			case DEVIDE:
				std::cout << "  /";
				break;
			case SIN:
				std::cout << "  sin";
				break;
			case COS:
				std::cout << "  cos";
				break;
			case PI:
				std::cout << "  pi";
				break;
			case NUMBER:
				std::cout << " " << currentLeaf->number;
				break;
			case VARIABLE:
				std::cout << " " << currentLeaf->variable;
				break;
			default:
				break;
	}
}
