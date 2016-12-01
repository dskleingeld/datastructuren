/**
* main: shows a menu with several options to input and evaluate regular
* expressions
* @author Eva van Houten (s1478621)
* @author David Kleingeld (s1432982)
* @file main.cpp
* @date datum laatste wijziging
**/

#include <string>
#include <iostream>
#include <fstream>
#include "Boom.h"
#include "Automaton.h"

void mainloop(std::string input, bool& done, Automaton*& automaton) {
	std::string expression;
	std::string input_value;
	std::string filename;
	std::string menuAction;

	if( input == "end"){
		done = true;
		return;
	}

	int sep = input.find(' ',0);//loc of space that seperates arguments
	menuAction = input.substr(0, sep);

	if (menuAction == "exp") {
		expression = input.substr(sep+1);
		Boom boom(expression);
        automaton = new Automaton(boom.getRoot());
        #ifdef DEBUG
        automaton->print(std::cout);
        #endif
	}
	else if (menuAction == "dot") {
		filename = input.substr(sep+1);
        if(automaton){
            automaton->toDot(filename);
        } else {
            std::cout << "Enter an expression first" << std::endl;
        }
	}
	else if (menuAction == "mat") {
		std::string toCheck = input.substr(sep+1);
		if(toCheck == "$"){ //the empty string
			toCheck = "";
		}
		if(automaton->checkString(toCheck, 0)){
			std::cout << "The string matches!" << std::endl;
		}else{
			std::cout << "The string doesn't match." << std::endl;
		}
	}
	else if (menuAction == "end") {
		done = true;
		return;
	}
	else {
		std::cout << "Invalid input" << std::endl;
		input.clear();
	}
}

int main(int argc, char *argv[]){
	std::cout << "\nDatastructures" << std::endl << "Assignment 3: Patroonherkenning" << "\n\n";
	std::cout << "         MENU          " << std::endl;
	std::cout << " -------------------- " << std::endl;
	std::cout << "[ exp <expression>   ] - input a regular expression" << std::endl;
	std::cout << "[ dot <filename.dot> ] - Save graphical form of the exp to file" << std::endl;
	std::cout << "[ mat <string>       ] - check of string matches the regular expression" << std::endl;
	std::cout << "[ end                ] - Exit" << std::endl;
	std::cout << " -------------------- " << std::endl;
    
    Automaton* automaton = nullptr;
	bool done = false;
	std::string input;

	if (argc > 1) {
		// We assume argv[1] is a filename to open
		std::ifstream the_file(argv[1]);
		// Always check to see if file opening succeeded
		if (!the_file.is_open())
			std::cout << "Could not open file\n";
		else {
			// the_file.get ( x ) returns false if the end of the file
			// is reached or an error occurs
			while (!the_file.eof()) {
				getline(the_file, input);
				mainloop(input, done, automaton);
				if (done) { 
					return 0;
				}
				input.clear();
			}
		}
	}
	while (!done) {
		getline(std::cin, input);
		mainloop(input, done, automaton);
	}
	
	return 0;
}
