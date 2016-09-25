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
    * @param MaxSize: the maximum size of the array
    * @return A stack of type array and size n
    * @pre
    * @post
    **/
    ArrayStack();
    /**
    * @function empty()
    * @abstract Check if object ArrayStack is empty
    * @param
    * @return true (if stack is empty) or false (if stack is not empty)
    * @pre 
    * @post 
    **/
    bool empty();
    /**
    * @function clear()
    * @abstract Clear content of array stack
    * @param 
    * @return true (succes) or false (unable to clear stack, or stack was already empty)
    * @pre Stack of size n
    * @post Empty stack
    **/
    void clear();
    /**
    * @function push(newItem)
    * @abstract Add new item to top of the stack
    * @param newItem: new item to be added to the stack
    * @return true (succes) or false (could not add new item)
    * @pre Stack of size (0,1,...,n)
    * @post Stack of size (0,1,...,n+1)
    **/
    void push(T newItem);
    /**
    * @function pop()
    * @abstract Remove item from top of the stack
    * @param 
    * @return true (succes) or false (could not remove top item)
    * @pre Stack of size (0,1,...,n)
    * @post Stack of size (0,1,...,n-1)
    **/
    bool pop();
    /**
    * @function top(topItem)
    * @abstract Return item at the top of the stack, give output to user
    * @param topItem: the item at the top of the stack
    * @return true (succes) or false (there is no top item)
    * @pre Stack of size n
    * @post Stack of size n
    **/
    bool top(T & topItem);
    /**
    * @function size()
    * @abstract Find size of the array and store the index of the top element in a variable
    * @param 
    * @return index of top item
    * @pre Stack of size n
    * @post
    **/
	void size();
private:
    // Array of certain size n = MAXSIZE
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
		size();
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
		array[top_number] = 0;
		top_number = top_number - 1; 
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
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
	top_number = i;
}

#endif
