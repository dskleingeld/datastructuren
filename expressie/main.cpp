#include <iostream>
// Visual Studio compiler does not directly import <string> 
#include <string>
#include "Boom.h"

using namespace std;

string testInvoer = "/ + * 2 x cos ^ x 42 + a b";
//string testInvoer = "+ * 2 x cos 42";
Boom theBoom;

void process(string invoer){
	for (unsigned int i = 0; i < invoer.size(); i++) { //Make sure subscript does not go out of range
		string substring;
		while ((invoer[i] != ' ') && (invoer[i] != 0)) { // Empty space or end of string
			substring += invoer[i];
			i = i + 1;
		}
		theBoom.processInput(substring); // Create new node in Boom
	}
}


int main()
{	
	cout << "\nDatastructures" << endl << "Assignment 2: Boom" << "\n\n";
	process(testInvoer);

	cout << "Current expression: " << endl;
	theBoom.cleanStack();
	theBoom.traverseTree();
	cout << endl;

//Because windows is being annoying
	string temp;
	cin >> temp;

	return 0;
}
