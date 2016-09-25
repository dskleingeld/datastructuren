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
	T inputstack;
	T outputstack;

	char topItem = 0;  
    int j = 0;
    // Backspace simulation: When an * is encountered, the previous character will be deleted.
    while (input[j] != 0 && input[j] != ' ') {
        if (input[j] == '*') {
            inputstack.pop(); // Delete char
            j = j + 1;
        }
        else {
		    inputstack.push(input[j]);
		    j = j + 1;
		}
	}
    // Pop items from inputstack:
    while (!inputstack.empty()) {
        // Display top item
        inputstack.top(topItem);
        // We want to reverse the order of inputstack. Therefore, place input in new stack (outputstack)
        outputstack.push(topItem);
        // Pop top item
        inputstack.pop();  
    }
    // Display outputstack:
    while (!outputstack.empty()) {
        // Display top item
        outputstack.top(topItem);
        cout << topItem;
        // Pop top item
        outputstack.pop();  
    }
	
    // Check if both stacks are empty
	inputstack.clear();
	if (inputstack.empty() && outputstack.empty()) {
		cout << "\nCleanup succeeded.\n" << endl;
	}
	else {
		cout << "\nUnable to clear Stacks.\n" << endl;
	}	
}

int main()
{	
	cout << "\nDatastructures" << endl << "Assignment 1: Stacks" << "\n\n";

	// Read a "word", untill the first break.
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
	
	int temp = 0;
	cin >> temp;
	return 0;
}
