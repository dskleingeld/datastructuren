/**
* Class name: ArrayStack, classical array stack
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld ( )
* @file arraystack.h
* @date 08-09-2016
**/

#ifndef ArrayStack_h
#define ArrayStack_h

#define MaxSize 40

template <class T>
class ArrayStack {
public:
    ArrayStack();//TODO shouldnt we pass the MaxSize to the constructor?
    bool empty();//as an agument
    void clear();
    bool push(T newItem);
    bool pop();
    bool top(T & topItem);
	void read();
	void size();
private:
    // Array of certain size
    T array[MaxSize];
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
ArrayStack<T>::ArrayStack() {
	for (int m = 0; m < MaxSize; m++) {
		array[m] = 0;
	}
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
bool ArrayStack<T>::empty() {
    if (array[0] == 0) {
        return true;
    }
    return false;
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
void ArrayStack<T>::clear() {
    while(!empty() ) {
		pop();
    }
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
bool ArrayStack<T>::push(T newItem) {

    // TODO: Check if number of items in array will not exceed maximum (which is -40-), if it does, return false
	if (empty()) {
		array[0] = newItem;
	}
	else {
		size(); // Find top_number
		if (top_number + 1 != MaxSize) {
			array[top_number + 1] = newItem;	
		}
		else return false;
	}
	return true;
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
bool ArrayStack<T>::pop() {
	if (!empty()) // Find top item
	{	
		size();
		array[top_number] = 0; // Pop 
		return true;
	}
	else // Array is empty
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

/**
* @function size()
* @abstract Find size of the array and store the index of the top element in a variable
* @param 
* @return index of top item
* @pre
* @post
**/
template <class T>
void ArrayStack<T>::size() {
	int i = 0;
    // Find top item
    if( !empty() ) { 
		// Array is not empty
		while (array[i + 1] != 0) {		
			i = i + 1;
		}
		top_number = i; // Remember this for later use
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
void ArrayStack<T>::read() {
	for (int k = 0; k < 40; k++) {
		std::cout << array[k];
	}
}

#endif
