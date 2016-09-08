#include <iostream>
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
	// Lees een "woord" in, tot de eerste spatie
	string invoer;
	cin >> invoer;

    // Voer vier keer dezelfde test uit, op verschillende implementaties.
	// Voor je datastructuur ArrayStack, bijvoorbeeld:
	backspace<ArrayStack<char> >(invoer);

	return 0;
}
