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
  	VectorStack();
  	bool empty();//as an argument
  	void clear();
  	void push(T newItem);
  	bool pop();
  	bool top(T & topItem);
	void read();
private:   
  	std::vector<T> vect;
	// Variable to keep track of the top of the array
	int top_number;
};

/**
* @function VectorStack()
* @abstract Constructor: Create object VectorStack
* @param
* @return VectorStack object
* @pre
* @post
**/
template <class T>
VectorStack<T>::VectorStack() { 
}
	
/**
* @function empty()
* @abstract Check if object VectorStack is empty
* @param 
* @return true (is empty) or false (is not empty)
* @pre 
* @post 
**/
template <class T>
bool VectorStack<T>::empty() {
    return vect.empty();
}

/**
* @function clear()
* @abstract Clear content of VectorStack
* @param 
* @return true (succes) or false (something did not work)
* @pre Stack of n elements
* @post Stack of 0 elements
**/
template <class T>
void VectorStack<T>::clear() {
  vect.clear();
}

/**
* @function push(T newItem)
* @abstract Add newItem to top of the stack
* @param newItem: new item to be added to the stack
* @return true (succes) or false (something did not work)
* @pre VectorStack of n elements, newItem
* @post VectorStack of n+1 elements
**/
template <class T>
void VectorStack<T>::push(T newItem) {
  vect.push_back(newItem);
}

/**
* @function pop()
* @abstract Remove item from top of the stack
* @param 
* @return true (succes) or false (something did not work)
* @pre VectorStack of n elements
* @post VectorStack of n-1 elements
**/
template <class T>
bool VectorStack<T>::pop() {
	if (!empty())
	{	
    vect.pop_back();
		return true;
	}
	else // vect must be empty
	{
		return false;
	}
}

/**
* @function top(topItem)
* @abstract Return item at the top of the stack, give output to user
* @param topItem: the item at the top of the stack
* @return true (succes) or false (something did not work)
* @pre VectorStack of n elements
* @post VectorStack of n elements
**/
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


/**
* @function read() //TODO ask how output and ostream works and if is nesessairy?
* @abstract Read the data in VectorStack and give output to user
* @param 
* @return 
* @pre
* @post
**/
template <class T>
void VectorStack<T>::read() {
  for (unsigned int i=vect.size()-1; i>0; i--)
    std::cout << vect[i];
  std::cout << vect[0];//do last element
}

#endif
