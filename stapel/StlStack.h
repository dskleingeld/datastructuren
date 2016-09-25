/**
* Class name: StlStack, wrapper around the standard libery stack
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file arraystack.h
* @date 16-09-2016
**/

#include <iostream>
#include <stack>

#ifndef StlStack_h
#define StlStack_h

template <class T>
class StlStack {
public:
    /**
    * @function StlStack()
    * @abstract Constructor: Create new STL stack
    * @param
    * @return 
    * @pre 
    * @post 
    **/
    StlStack();
    /**
    * @function empty()
    * @abstract Check if container in stack is empty
    * @param
    * @return true (is empty) or false (is not empty)
    * @pre 
    * @post 
    **/
    bool empty();
    /**
	* @function clear()
	* @abstract Clear content of stack
	* @param
	* @return true (succes) or false (unable to clear stack, or stack was already empty)
	* @pre Stack of size n
	* @post Empty stack
    **/
    void clear();
    /**
    * @function push(newItem)
    * @abstract Add newItem to top of the stack
    * @param newItem: new item to be added to the stack
    * @return
    * @pre stack of n elements
    * @post stack of n+1 elements
    **/
    void push(T newItem);
    /**
    * @function pop()
    * @abstract Remove item from top of the stack
    * @param none
    * @return false if there is no element to pop else true
    * @pre pointer to first element
    * @post pointer to second element and first element deleted
    **/
    bool pop();
    /**
    * @function top(topItem)
    * @abstract Return item at the top of the stack, give output to user
    * @param topItem: the item at the top of the stack
    * @return true (succes) or false (if there is no item)
    * @pre stack of n elements
    * @post stack of n elements
    **/
    bool top(T & topItem);
private:
    std::stack<T> Stack;
};

template <class T>
StlStack<T>::StlStack() {
}

template <class T>
bool StlStack<T>::empty() {
    if (Stack.empty()) {
        return true;
    }
    else {
        return false;
    } 
}

template <class T>
void StlStack<T>::clear() {
    while(!empty() ) {
		Stack.pop();
    }
}

template <class T>
void StlStack<T>::push(T newItem) {
    Stack.push(newItem);
}

template <class T>
bool StlStack<T>::pop() {
    if (empty()) {
        return false;
    }
    Stack.pop();
    return true;
}

template <class T>
bool StlStack<T>::top(T & topItem) {
    if (empty()) {
        return false;
    }
    topItem = Stack.top();
    return true;
}

#endif

