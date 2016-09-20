/**
* Class name: ArrayStack, classical array stack
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld ( )
* @file arraystack.h
* @date 08-09-2016
**/
#include <vector>

#ifndef VectorStack_h
#define VectorStack_h

template <class T>
class VectorStack {
public:
  VectorStack();//TODO shouldnt we pass the MaxSize to the constructor?
  bool empty();//as an agument
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
* @function ArrayStack()
* @abstract Constructor: Create object ArrayStack, filled with 0s
* @param MaxSize: the size of the array
* @return 
* @pre
* @post empty ArrayStack object
**/
template <class T>
VectorStack<T>::VectorStack() { 
}
	
/**
* @function empty()
* @abstract Check if object ArrayStack is empty
* @param none
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
* @abstract Clear content of array stack, delete array
* @param none
* @return true (succes) or false (something did not work)
* @pre Filled stack of type array
* @post Empty stack
**/
template <class T>
void VectorStack<T>::clear() {
  vect.clear();
}

/**
* @function push(newItem)
* @abstract Add newItem to top of the stack
* @param newItem: new item to be added to the stack
* @return true (succes) or false (something did not work)
* @pre Stack of type array
* @post Stack of type array, with new item at top
**/
template <class T>
void VectorStack<T>::push(T newItem) {
  vect.push_back(newItem);
}

/**
* @function pop()
* @abstract Remove item from top of the stack
* @param none
* @return true (succes) or false (something did not work)
* @pre Stack of type array
* @post Stack of type array, with top item removed
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
* @pre Stack of type array
* @post Stack of type array
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
* @function output(ostream & out) //TODO ask how output and ostream works and if is nesessairy?
* @abstract Use ostream to give output to user
* @param out: the data to return
* @return output
* @pre input
* @post output
**/
template <class T>
void VectorStack<T>::read() {
  for (unsigned int i=vect.size()-1; i>0; i--)
    std::cout << vect[i];
  std::cout << vect[0];//do last element
}

#endif
