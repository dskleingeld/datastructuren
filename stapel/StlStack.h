#include <iostream>
#include <stack>

#ifndef StlStack_h
#define StlStack_h

template <class T>
class StlStack {
public:
    StlStack();
    bool empty();
    void clear();
    void push(T newItem);
    bool pop();
    bool top(T & topItem);
	void read();
private:
    std::stack<T> Stack;
};

/**
* @function StlStack()
* @abstract Constructor: Create new object node
* @param
* @return 
* @pre 
* @post 
**/
template <class T>
StlStack<T>::StlStack() {
}

/**
* @function empty()
* @abstract Check if container in stack is empty
* @param none
* @return true (is empty) or false (is not empty)
* @pre 
* @post 
**/
template <class T>
bool StlStack<T>::empty() {
    if (Stack.empty()) {
        return true;
    }
    else {
        return false;
    } 
}

/**
* @function clear()
* @abstract Clear content of the stack, delete every element
* @param none
* @return
* @pre pointer to filled stack
* @post Empty stack
**/
template <class T>
void StlStack<T>::clear() {
    while(!empty() ) {
		Stack.pop();
    }
}

/**
* @function push(newItem)
* @abstract Add newItem to top of the stack
* @param newItem: new item to be added to the stack
* @return
* @pre stack of n elements
* @post stack of n+1 elements
**/
template <class T>
void StlStack<T>::push(T newItem) {
    Stack.push(newItem);
}

/**
* @function pop()
* @abstract Remove item from top of the stack
* @param none
* @return false if there is no element to pop else true
* @pre pointer to first element
* @post pointer to second element and first element deleted
**/
template <class T>
bool StlStack<T>::pop() {
    if (empty()) {
        return false;
    }
    Stack.pop();
    return true;
}

/**
* @function top(topItem)
* @abstract Return item at the top of the stack, give output to user
* @param topItem: the item at the top of the stack
* @return true (succes) or false (if there is no item)
* @pre stack of n elements
* @post stack of n elements
**/
template <class T>
bool StlStack<T>::top(T & topItem) {
    if (empty()) {
        return false;
    }
    topItem = Stack.top();
    return true;
}

template <class T>
void StlStack<T>::read() {//TODO not in assaignment should we keep?
    while (!empty()) {
        std::cout << Stack.top();
        Stack.pop();
    }
}

#endif

