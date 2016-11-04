#include <iostream>
// Visual Studio compiler does not directly import <string> 
#include <string>
#include "Boom.h"

using namespace std;

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
	cout << "Options:" << endl << "--------------" << endl << "exp <expression>" << endl << "print" << endl << "dot <filename.dot>" << endl;
	cout << "eval <value>" << endl << "diff" << endl << "simp" << endl << "end" << endl << "--------------" << endl;

	string testInvoer = "/ + * 2 x cos + 8 ^ x + 3 y + a / + / pi 5 871 0";
	string input;
	string expression;
	string variable = "x";
	string input_value;
	double value;

	// This is a user menu:
	bool done = false; 

	// A loop to go through the various input possibilities, TODO: switch statement?
	while (!done) {
		string substring;
		getline(cin, input);
		int i = 0;
		while ((input[i] != ' ') && (input[i] != 0)) {
			// Empty space or end of string
			substring += input[i];
			i = i + 1;
		}
		if (substring == "exp") {
			while (input[i] == ' ') { // Delete empty spaces in imput
				i = i + 1;
			}
			while (input[i] != 0) { // End of string
				expression += input[i];
				i = i + 1;
			}
			process(expression);
		}
		else if (substring == "dot") {
			// TODO
		}
		else if (substring == "print") {
			cout << "Current expression: " << endl;
			theBoom.view();
			cout << endl;
		}
		else if (substring == "eval") {
			if (input[i] != 0) {
				while (input[i] == ' ') { // Delete empty spaces in imput
					i = i + 1;
				}
				while ((input[i] != ' ') && (input[i] != 0)) { // Empty space or end of string
					input_value += input[i];
					i = i + 1;
				}
				value = std::atof(input_value.c_str()); // Convert to number
				theBoom.Evaluate(variable, value);
			}
		}
		else if (substring == "diff") {
			// TODO
		}
		else if (substring == "simp") {
			theBoom.Simplify();
		}
		else if (substring == "end") {
			done = true;
		}
	}
	
	return 0;
}
