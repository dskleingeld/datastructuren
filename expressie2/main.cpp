#include <iostream>
#include <string>
#include "Boom.h"
#include <fstream>
#include <cstdlib>

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

void mainloop(string input, bool& done) {
	string expression;
	string variable = "x";
	string input_value;
	string filename;
	string substring;
	double value;
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
		theBoom->graph_dot(filename.c_str());
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
		return;
	}
	else {
		cout << "Invalid input" << endl;
		input.clear();
	}
}

int main(int argc, char *argv[])
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

	bool done = false;
	string input;

	if (argc > 1) {
		// We assume argv[1] is a filename to open
		ifstream the_file(argv[1]);
		// Always check to see if file opening succeeded
		if (!the_file.is_open())
			cout << "Could not open file\n";
		else {
			// the_file.get ( x ) returns false if the end of the file
			//  is reached or an error occurs
			while (!the_file.eof()) {
				getline(the_file, input);
				mainloop(input, done);
				if (done) { 
					return 0;
				}
				input.clear();
			}
		}
	}
	while (!done) {
		getline(cin, input);
		mainloop(input, done);
	}
	
	return 0;
}
