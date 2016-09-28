#include "Boom.h"

Boom::Boom(){
	root = new leaf;
}

Boom::add(string substring){
	typeOfLeaf operant;
	switch(kar)://TODO werkt niet met SIN...
		case '+':
			operant = PLUS;
			break;
		case '-':
			operant = MINUS;
			break;
		case '*':
			operant = TIMES;
			break;			
		case '^':
			operant = POWER;
			break;				
		case '^':
			operant = DEVIDE;
			break;
		default:
			if (kar > 47 && kar < 58){
				tonumber(kar)
				operant = NUMBER;
			else:
				operant = VARIABLE;
			break
	
	else if is number?:
		tonumber(substring)
	else if is sin/cos/pi:
		operant = SIN;
		
	//TODO
	//really add a leaf with pointers and such
		


