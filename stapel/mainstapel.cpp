#include <iostream>
// Visual Studio compiler does not directly import <string> 
#include <string>
#include "PointerStack.h"
#include "ArrayStack.h"

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
	/*
	cout << "Give me input to stack: ";
	string invoer;
	getline(cin, invoer);
	menu(invoer);
	*/
	string input = "helloworld";
	cout << "Input is: " << input << endl;
	char item;
	 
    ArrayStack<char> arrayStack;
    int j = 0;
    while (input[j] != 0 && input[j] != ' ') {
		if (arrayStack.push(input[j])) {
			j = j + 1;
		}
		else // Teveel input
		{
			cout << "Too much input. Error!" << endl;
		}
	}
	
    arrayStack.top(item);
    cout << "Top item: " << item << "\n\n";
    arrayStack.pop();
    cout << "Pop" << endl;
	
	cout << "Array stack reads: ";
    arrayStack.read();
    cout << "\n\n";
    
    // Check if ArrayStack is empty
	arrayStack.clear();
	if (arrayStack.empty()) {
		cout << "Cleanup succeeded." << endl;
	}
	else {
		cout << "Unable to clear ArrayStack." << endl;
	}
		
	// Voer vier keer dezelfde test uit, op verschillende implementaties.
	// Voor je datastructuur ArrayStack, bijvoorbeeld:
	// backspace<ArrayStack<char> >(invoer);
	return 0;
}
