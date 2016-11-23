#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Boom.h"

using namespace std;


void mainloop(string input, bool& done) {
	string expression;
	string input_value;
	string filename;
	string menuAction;

	if( input == "end"){
		done = true;
		return;
	}

	int sep = input.find(' ',0);//loc of space that seperates arguments
	menuAction = input.substr(0, sep);

	if (menuAction == "exp") {
		expression = input.substr(sep+1);
		Boom Boom(expression);
	}
	else if (menuAction == "dot") {
		//TODO
	}
	else if (menuAction == "print") {
		//TODO
	}
	else if (menuAction == "eval") {
		//TODO
	}
	else if (menuAction == "end") {
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
	cout << "\nDatastructures" << endl << "Assignment 3: Patroonherkenning" << "\n\n";
	cout << "         MENU          " << endl;
	cout << " -------------------- " << endl;
	cout << "[ exp <expression>   ] - input a regular expression" << endl;
	cout << "[ dot <filename.dot> ] - Save graphical form of the exp to file" << endl;
	cout << "[ mat <string>       ] - check of string matches the regular expression" << endl;
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
			// is reached or an error occurs
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
