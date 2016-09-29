#include <iostream>
// Visual Studio compiler does not directly import <string> 
#include <string>
#include "Boom.h"

using namespace std;

string testInvoer = "+ 2 42";
Boom theBoom;

void process(string invoer){
	int i = 0; // Invoer counter
	while (invoer[i] != 0) { // End of string
		string substring;
		while ((invoer[i] != ' ') && (invoer[i] != 0)) { // Empty space or end of string
			substring += invoer[i];
			i = i + 1;
		}
		cout << "substring: " << substring << endl;
		theBoom.processInput(substring); // Create new node in Boom
		i = i + 1;
	}

//	For string while not string end:
//		add substring
//		theBoom.add(std::string substring)
}


int main()
{	
	cout << "\nDatastructures" << endl << "Assignment 2: Boom" << "\n\n";
	process(testInvoer);
	theBoom.walkInorder();
	return 0;
}
