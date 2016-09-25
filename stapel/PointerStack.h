/**
* Class name: PointerStack, stack implemented using a singly connected list
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file PointerStack.h
* @date 20-09-2016
**/

#ifndef PointerStack_h
#define PointerStack_h

template <class T>
class node {
public:
    node<T>* next;
    T value;
};

template <class T>
class PointerStack {
public:
    /**
    * @function PointerStack()
    * @abstract Constructor: Create new object node
    * @param
    * @return object of class node
    * @pre 
    * @post 
    **/
    PointerStack();
    /**
    * @function empty()
    * @abstract Check if object PointerStack is empty
    * @param
    * @return true (is empty) or false (is not empty)
    * @pre 
    * @post 
    **/
    bool empty();
    /**
    * @function clear()
    * @abstract Clear content of the pointer stack, delete every element
    * @param
    * @return
    * @pre pointer to filled stack
    * @post Empty stack
    **/
    void clear();
    /**
	* @function push(newItem)
	* @abstract Add new item to top of the stack
	* @param newItem: new item to be added to the stack
	* @return true (succes) or false (could not add new item)
	* @pre Stack of n elements
	* @post Stack of n+1 elements
    **/
    void push(T newItem);
    /**
    * @function pop()
    * @abstract Remove item from top of the pointer stack
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
    node<T>* topElement;//stores the highest element in the stack
};

template <class T>
PointerStack<T>::PointerStack() {
    topElement = new node<T>;
    topElement->next = NULL;
}

template <class T>
bool PointerStack<T>::empty() {
    if (topElement == NULL) {
        return true;
    }
    return false;
}

template <class T>
void PointerStack<T>::clear() {
   while (topElement != NULL) {
       pop(); 
   }
}

template <class T>
void PointerStack<T>::push(T newItem) {
    node<T>* old_top;
    old_top = topElement;
    
    topElement = new node<T>;
    topElement->next = old_top;
    
    topElement->value = newItem;
}

template <class T>
bool PointerStack<T>::pop() {
    node<T>* old_top;
    old_top = topElement;
    
    if (!empty() ){
        topElement = topElement->next;
        delete old_top;
        return true;
        }
    else{
        return false;
    }  
}

template <class T>
bool PointerStack<T>::top(T & topItem) {
    if (empty() ) { return false;}
    else{
        topItem = topElement->value;
        return true;
    }
}

#endif
