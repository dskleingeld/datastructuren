#include <iostream>
// Visual Studio compiler does not directly import <string> 
#include <string>
#include "PointerStack.h"
#include "ArrayStack.h"
#include "StlStack.h"
#include "VectorStack.h"

using namespace std;

template<class T>
void backspace(string input)
{
	T invoerstack;

	char topItem = 0;  
    int j = 0;
    // Backspace simulation: When an * is encountered, the previous character will be deleted.
    while (input[j] != 0 && input[j] != ' ') {
        if (input[j] == '*') {
            invoerstack.pop(); // Delete char
            j = j + 1;
        }
        else {
		    invoerstack.push(input[j]);
		    j = j + 1;
		}
	}

    // Display top item
    invoerstack.top(topItem);
    cout << "Top item: " << topItem << "\n";
    // Pop top item
    invoerstack.pop();
    cout << "Pop" << endl;
	
	// Display the content of the stack, in the case of STL stack this clears the stack (so, only do this at the end).
	cout << "Stack reads: ";
    invoerstack.read();
    cout << "\n";
    
    // Check if stack is empty
	invoerstack.clear();
	if (invoerstack.empty()) {
		cout << "Cleanup succeeded.\n" << endl;
	}
	else {
		cout << "Unable to clear ArrayStack.\n" << endl;
	}	
}

int main()
{	
	cout << "\nDatastructures" << endl << "Assignment 1: Stacks" << "\n\n";
	/*
	// Read a "word", untill the first break.
	cout << "Give me input to stack: ";
	string invoer;
	getline(cin, invoer);
	*/
	string input = "helll*oww*orld";
	cout << "Initial input is: " << input << "\n\n";

	// Run the same test for each of the four implementations.
	ArrayStack<char> arrayStack;
	cout << "ArrayStack:\n";
	backspace<ArrayStack<char> >(input);
	PointerStack<char> pointerStack;
	cout << "PointerStack:\n";
	backspace<PointerStack<char> >(input);
	cout << "STL Stack:\n";	
	StlStack<char> stlstack;	
	backspace<StlStack<char> >(input);
	cout << "VectorStack:\n";	
	VectorStack<char> vectorStack;	
	backspace<VectorStack<char> >(input);	
	return 0;
}
