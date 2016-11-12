#include <iostream>
// Visual Studio compiler does not directly import <string> 
#include <string>
#include "Boom.h"

using namespace std;

Boom* theBoom;

void process(string invoer){
	for (unsigned int i = 0; i < invoer.size(); i++) { 
		//Make sure subscript does not go out of range
		string substring;
		while ((invoer[i] != ' ') && (invoer[i] != 0)) { 
			// Empty space or end of string
			substring += invoer[i];
			i = i + 1;
		}
		theBoom->processInput(substring); // Create new node in Boom
	}
}


int main()
{	
	cout << "\nDatastructures" << endl << "Assignment 2: Boom" << "\n\n";
	cout << "         MENU          " << endl;
	cout << " -------------------- " << endl;
	cout << "[ exp <expression>   ] - (Use post order notation) Create an expression tree" << endl; 
	cout << "[ print              ] - Print tree" << endl;
	cout << "[ dot <filename.dot> ] - Save graphical display of tree to file" << endl;
	cout << "[ eval <value>       ] - Evaluate f(x) for  x = <value>" << endl;
	cout << "[ diff               ] - Differentiate d(f(x)/dx" << endl;
	cout << "[ simp               ] - Simplify tree" << endl;
	cout << "[ end                ] - Exit" << endl;
	cout << " -------------------- " << endl;

	string testInvoer = "/ + * 2 x cos + 8 ^ x + 3 y + a / + / pi 5 871 0";
	string input;
	string expression;
	string variable = "x";
	string input_value;
	string filename;
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
			delete theBoom;
			theBoom = new Boom;
			while (input[i] == ' ') { // Delete empty spaces in imput
				i = i + 1;
			}
			while (input[i] != 0) { // End of string
				expression += input[i];
				i = i + 1;
			}
			process(expression);
			input.clear();
			expression.clear();
		}
		else if (substring == "dot") {
			while (input[i] == ' ') { // Delete empty spaces in imput
				i = i + 1;
			}
			while (input[i] != 0) { // End of string
				filename += input[i];
				i = i + 1;
			}
			theBoom->graph_dot(filename);
			filename.clear();
		}
		else if (substring == "print") {
			cout << "Current expression: " << endl;
			theBoom->view();
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
				theBoom->evaluate(variable, value);
			}
		}
		else if (substring == "diff") {
			theBoom->differentiate(variable[0]);
		}
		else if (substring == "simp") {
			theBoom->simplify();
		}
		else if (substring == "end") {
			done = true;
		}
		else {
			cout << "Invalid input" << endl;
			input.clear();
		}
	}
	
	return 0;
}
