/**
* Class name: ArrayStack, classical array stack
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file arraystack.h
* @date 08-09-2016
**/

#ifndef ArrayStack_h
#define ArrayStack_h

#define MAXSIZE 10000

template <class T>
class ArrayStack {
public:
    /**
    * @function ArrayStack()
    * @abstract Constructor: Create object ArrayStack, filled with 0s
    * @param MaxSize: the size of the array
    * @return 
    * @pre
    * @post empty ArrayStack object
    **/
    ArrayStack();
    /**
    * @function empty()
    * @abstract Check if object ArrayStack is empty
    * @param none
    * @return true (is empty) or false (is not empty)
    * @pre 
    * @post 
    **/
    bool empty();
    /**
    * @function clear()
    * @abstract Clear content of array stack, delete array
    * @param none
    * @return true (succes) or false (something did not work)
    * @pre Filled stack of type array
    * @post Empty stack
    **/
    void clear();
    /**
    * @function push(newItem)
    * @abstract Add newItem to top of the stack
    * @param newItem: new item to be added to the stack
    * @return true (succes) or false (something did not work)
    * @pre Stack of type array
    * @post Stack of type array, with new item at top
    **/
    void push(T newItem);
    /**
    * @function pop()
    * @abstract Remove item from top of the stack
    * @param none
    * @return true (succes) or false (something did not work)
    * @pre Stack of type array
    * @post Stack of type array, with top item removed
    **/
    bool pop();
    /**
    * @function top(topItem)
    * @abstract Return item at the top of the stack, give output to user
    * @param topItem: the item at the top of the stack
    * @return true (succes) or false (something did not work)
    * @pre Stack of type array
    * @post Stack of type array
    **/
    bool top(T & topItem);
    /**
    * @function size()
    * @abstract Find size of the array and store the index of the top element in a variable
    * @param 
    * @return index of top item
    * @pre
    * @post
    **/
	void size();
private:
    // Array of certain size
    T array[MAXSIZE];
	// Variable to keep track of the top of the array
	int top_number;
};

template <class T>
ArrayStack<T>::ArrayStack() { 
	for (int m = 0; m < MAXSIZE; m++) {
		array[m] = 0;
	}
}
	
template <class T>
bool ArrayStack<T>::empty() {
    if (array[0] == 0) {
        return true;
    }
    return false;
}

template <class T>
void ArrayStack<T>::clear() {
    while(!empty() ) {
		pop();
    }
}

template <class T>
void ArrayStack<T>::push(T newItem) {
	if (empty()) {
		array[0] = newItem;
	}
	else {
		size(); // Find top_number
		if (top_number + 1 != MAXSIZE) {
			array[top_number + 1] = newItem;	
		}
		else {
		    std::cout << "Too much input\n";
	    }
	}
}

template <class T>
bool ArrayStack<T>::pop() {
	if (!empty())
	{	
		size();
		array[top_number] = 0; // Pop
		top_number = top_number - 1; 
		return true;
	}
	else // Array is empty
	{
		return false;
	}
}

template <class T>//TODO maybe a var that keeps the top element?
bool ArrayStack<T>::top(T & topItem) {
	if (!empty()) {
		size();
		topItem = array[top_number];
	    return true;
	}
	else {
		return false;
	}
}

template <class T>
void ArrayStack<T>::size() {
	int i = 0;
	while (array[i + 1] != 0) {		
		i = i + 1;
	}
	top_number = i; // Remember this for later use
}

#endif
