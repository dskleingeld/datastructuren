#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;


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
		//TODO
	}
	else if (substring == "dot") {
		//TODO
	}
	else if (substring == "print") {
		//TODO
	}
	else if (substring == "eval") {
		//TODO
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
