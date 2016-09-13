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

template<class T>
void submenu(T submenu_stack) {
	cout << "[S] Display stack" << endl;
	cout << "[T] Display item on top" << endl;
	cout << "[C] Clear stack" << endl;
	cout << "[E] Exit to main menu" << endl;
	char submenu_choice;
	bool switch_on = true;
	while (switch_on) {
		cin >> submenu_choice;
		switch (submenu_choice) {
		case 'S':
		{
			cout << "Array stack now reads: ";
			submenu_stack.read();
			cout << endl;
			break;
		}
		case 'T':
		{
			char topItem = 0;
			submenu_stack.top(topItem);
			cout << "The item on top is: " << topItem << endl;
			break;
		}
		case 'C':
		{
			// Check if ArrayStack is empty
			if (submenu_stack.empty()) {
				cout << "The ArrayStack is empty" << endl;
			}
			else {
				submenu_stack.clear();
				if (submenu_stack.empty()) {
					cout << "Cleanup succeeded. The ArrayStack is now empty" << endl;
				}
				else {
					cout << "Unable to clear ArrayStack. Not emptied." << endl;
				}
			}
			break;
		}
		case 'E':
		{
			switch_on = false;
			break;
		}
		default:
			break;
		}
	}
}

void menu(string invoer) {
	bool switch_on = true;
	while (switch_on) {
		cout << "<< Menu >>" << endl;
		cout << "A: Array Stack" << endl << "B: Pointer Stack" << endl << "C: Vector Stack" << endl << "D: Stack" << endl;
		cout << "---" << endl << "[E] Exit" << endl;
		char menu_choice;
		cin >> menu_choice;
		switch (menu_choice)
		{
		case 'A':
		{
			// First: char in array_stack
			int j = 0;
			ArrayStack<char> stack;
			if (invoer[0] != 0) {
				bool input = true;
				while (input) {
					if (invoer[j] != 0 && invoer[j] != ' ') {
					//TODO waarom deze if niet als voorwaarde van de while statment?
						stack.push(invoer[j]);
						j = j + 1;
					}
					else {
						input = false;
					}
				}
			}
			submenu<ArrayStack<char> >(stack);
			break;
		}
		case 'B':
		{
			// First: char in array_stack
			int j = 0;
			PointerStack<char> stack;
			if (invoer[0] != 0) {
				bool input = true;
				while (input) {
					if (invoer[j] != 0 && invoer[j] != ' ') {
					//TODO waarom deze if niet als voorwaarde van de while statment?
						stack.push(invoer[j]);
						j = j + 1;
					}
					else {
						input = false;
					}
				}
			}
			submenu<PointerStack<char> >(stack);
			break;
		}
		case 'E':
		{
			cout << "Bye";
			switch_on = false;
			break;
		}
		default:
			break;
		}
	}
}

int main()
{	
	cout << "Datastructures" << endl << "Assignment 1: Stacks" << endl << "***" << endl;
	// Lees een "woord" in, tot de eerste spatie
	cout << "Give me input to stack: ";
	string invoer;
	getline(cin, invoer);
	menu(invoer);

	// Voer vier keer dezelfde test uit, op verschillende implementaties.
	// Voor je datastructuur ArrayStack, bijvoorbeeld:
	//backspace<ArrayStack<char> >(invoer);
	return 0;
}
