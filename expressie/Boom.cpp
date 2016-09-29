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
	char variable;
	double number;

	char kar = substring[0];		
	if (substring.length() == 1) { //TODO
		switch(kar) {
			case '+':
				operand = PLUS;
				std::cout << "PLUS" << std::endl;
				break;
			case '-':
				operand = MINUS;
				std::cout << "MINUS" << std::endl;
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
					std::cout << "NUMBER" << std::endl;
					number = (double)(kar-48);//-48 to go to normal numbers from ascii
				}
				else{ operand = VARIABLE; }
					variable = kar;
				break;
		}
	}
	else if (stringIsNumber(substring)) {
		number = std::atof(substring.c_str() );
		std::cout << "DOUBLE NUMBER" << std::endl;
	}
	//TODO: test if sin, cos or pi
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
	//TODO: really add a leaf with pointers and such
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
	
	//Determine how many children this node has (0, 1 or 2)
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

