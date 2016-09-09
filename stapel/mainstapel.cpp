#include <iostream>
// Visual Studio compiler does not directly import <string> 
#include <string>
#include "arraystack.h"

using namespace std;

template<class T>
void backspace(string invoer)
{
	T invoerstack;

	// Nog te implementeren: "backspace simulatie"
	invoerstack.push(invoer[0]);
	invoerstack.push('b');
	invoerstack.pop();

	// Nog te implementeren: Resultaat uitvoeren
	char topItem = 0;
	cout << invoerstack.top(topItem);
	cout << topItem;
	cout << endl;
}

int main()
{
	cout << "Datastructures" << endl << "Assignment 1: Stacks" << endl << "***" << endl;
	// Lees een "woord" in, tot de eerste spatie
	cout << "Give me input to stack: ";
	string invoer;
	getline(cin, invoer);
	
	// First: char in array_stack
	int j = 0;
	ArrayStack<char> array_stack;
	if (invoer[0] != 0) { 
		bool input = true; 
		while (input) {
			if (invoer[j] != 0 && invoer[j] != ' ') {
				array_stack.push(invoer[j]);
				j = j + 1;
			}
			else {
				input = false;
			}
		}
	}
	cout << "Array stack now reads: ";
	array_stack.read();
	cout << endl;

	char topItem = 0;
	array_stack.top(topItem);
	cout << "The item on top is: " << topItem << endl;

    // Voer vier keer dezelfde test uit, op verschillende implementaties.
	// Voor je datastructuur ArrayStack, bijvoorbeeld:
	//backspace<ArrayStack<char> >(invoer);

	array_stack.clear();
	cout << "exit? (type something)" << endl;
	string temp;
	cin >> temp;
	return 0;
}
