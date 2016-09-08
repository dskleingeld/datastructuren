/**
* Class name: ArrayStack, classical array stack
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld ( )
* @file arraystack.h
* @date 08-09-2016
**/

#ifndef Arraystack_h
#define Arraystack_h

template <class T>
class ArrayStack {
private:
    // Array of size -40-
    char array[40];
public:
    ArrayStack();
    bool isEmpty();
    void clear();
    bool push(char newItem);
    bool pop();
    bool top(char topItem);
//protected:
//    void output(ostream & out);
};

/**
* @function ArrayStack()
* @abstract Constructor: Create object ArrayStack
* @param 
* @return 
* @pre 
* @post 
**/
template <class T>
ArrayStack<T>::ArrayStack() {}

/**
* @function isEmpty()
* @abstract Check if object ArrayStack is empty
* @param none
* @return true (is empty) or false (is not empty)
* @pre 
* @post 
**/
template <class T>
bool ArrayStack<T>::isEmpty() {
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
    int i = 0;
    while( array[i] != 0 ) {
        array[i] = 0;
        i = i + 1;
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
bool ArrayStack<T>::push(char newItem) {

    // TODO: Check if number of items in array will not exceed maximum (which is -40-), if it does, return false
    
    int i = 0;
    // Find top item
    if( array[i] == 0 ) {
        // Array is empty
        array[i] = newItem;
    }
    else {
        // Array is not empty
        while( array[i+1] != 0 ) {
            i = i + 1;
        }
        // Insert new item at top
        array[i+1] = newItem;
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
    int i = 0;
    // Find top item
    if( array[i] == 0 ) {
        // Array is already empty, nothing to do here
        return false;
    }
    else {
        // Array is not empty
        while( array[i+1] != 0 ) {
            i = i + 1;
        }
        // Remove item from top
        array[i] = 0;
    }
    return true;
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
bool ArrayStack<T>::top(char topItem) {
    int i = 0;
    // Find top item
    if( array[i] == 0 ) {
        // Array is empty, nothing to see here
        return false;
    }
    else {
        // Array is not empty
        while( array[i+1] != 0 ) {
            i = i + 1;
        }
        // Show item at top
        topItem = array[i];
    }
    return true;
}

/**
* @function output(ostream & out)
* @abstract Use ostream to give output to user
* @param out: the data to return
* @return output
* @pre input
* @post output
*
template <class T>
void ArrayStack<T>::output(ostream & out) {
    out << data;
}*/

#endif
