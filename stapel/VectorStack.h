/**
* Class name: VectorStack, stack implemented using the standardliberary stack
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file arraystack.h
* @date 20-09-2016
**/
#include <vector>

#ifndef VectorStack_h
#define VectorStack_h

template <class T>
class VectorStack {
public:
    /**
    * @function VectorStack()
    * @abstract Constructor: Create object VectorStack
    * @param
    * @return VectorStack object
    * @pre
    * @post
    **/
  	VectorStack();	
    /**
    * @function empty()
    * @abstract Check if object VectorStack is empty
    * @param 
    * @return true (is empty) or false (is not empty)
    * @pre 
    * @post 
    **/
  	bool empty();
    /**
    * @function clear()
    * @abstract Clear content of VectorStack
    * @param 
    * @return true (succes) or false (something did not work)
    * @pre Stack of n elements
    * @post Stack of 0 elements
    **/
  	void clear();
    /**
    * @function push(T newItem)
    * @abstract Add newItem to top of the stack
    * @param newItem: new item to be added to the stack
    * @return true (succes) or false (something did not work)
    * @pre VectorStack of n elements, newItem
    * @post VectorStack of n+1 elements
    **/
  	void push(T newItem);
    /**
    * @function pop()
    * @abstract Remove item from top of the stack
    * @param 
    * @return true (succes) or false (something did not work)
    * @pre VectorStack of n elements
    * @post VectorStack of n-1 elements
    **/
  	bool pop();
    /**
    * @function top(topItem)
    * @abstract Return item at the top of the stack, give output to user
    * @param topItem: the item at the top of the stack
    * @return true (succes) or false (something did not work)
    * @pre VectorStack of n elements
    * @post VectorStack of n elements
    **/
  	bool top(T & topItem);
private:   
  	std::vector<T> vect;
};

template <class T>
VectorStack<T>::VectorStack() { 
}

template <class T>
bool VectorStack<T>::empty() {
    return vect.empty();
}

template <class T>
void VectorStack<T>::clear() {
  vect.clear();
}

template <class T>
void VectorStack<T>::push(T newItem) {
  vect.push_back(newItem);
}

template <class T>
bool VectorStack<T>::pop() {
	if (!empty())
	{	
    vect.pop_back();
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
bool VectorStack<T>::top(T & topItem) {
	if (!empty()) {
    topItem = vect.back();
    return true;
	}
	else {
		return false;
	}
}

#endif
