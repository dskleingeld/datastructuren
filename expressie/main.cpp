#include <iostream>
// Visual Studio compiler does not directly import <string> 
#include <string>
#include "Boom.h"

using namespace std;

string testInvoer = "/ + * 2 x cos + 8 ^ x + 3 y + a / + / pi 5 871 0";
Boom theBoom;

void process(string invoer){
	for (unsigned int i = 0; i < invoer.size(); i++) { 
		//Make sure subscript does not go out of range
		string substring;
		while ((invoer[i] != ' ') && (invoer[i] != 0)) { 
			// Empty space or end of string
			substring += invoer[i];
			i = i + 1;
		}
		theBoom.processInput(substring); // Create new node in Boom
	}
}


int main()
{	
	cout << "\nDatastructures" << endl << "Assignment 2: Boom" << "\n\n";
	cout << "Input mathematical expression: ";
	//getline(cin, testInvoer);
	process(testInvoer);

	cout << "Current expression: " << endl;
	theBoom.view();
	cout << endl;
	return 0;
}
