#include <iostream>
// Visual Studio compiler does not directly import <string> 
#include <string>
#include "pointerstack.h"

using namespace std;

int main() {
    int item = 15;  
    pointerStack<int> Stack;
    Stack.push(item);
    Stack.top(item);
    std::cout << item << "\n\n";
    Stack.pop();

    Stack.read();

    Stack.push(item++);
    Stack.push(item++);    
    Stack.read();
    Stack.clear(); 
    Stack.read();
    
    if (Stack.empty() ){ std::cout << "stack is empty";}
} 




