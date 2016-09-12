/**
* Class name: ArrayStack, classical array stack
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld ( )
* @file arraystack.h
* @date 08-09-2016
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
    bool empty();//TODO named empty to conform to default c++ stack names
    void clear();
    void push(T newItem);
    void pop();
    void top(T & topItem);
	void read();
private:
    PointerStack();
    node<T>* topElement;//stores the highest element in the stack
};

/**
* @function PointerStack()
* @abstract Constructor: Create new object node
* @param
* @return 
* @pre 
* @post 
**/
template <class T>
PointerStack<T>::PointerStack() {
    topElement = new node<T>;
    topElement->next = NULL;
//    topElement->value = -1;//TODO would it be more efficient to fill this value
                             //in the top function?
}
//NOTE these are equivalent
//  a->b
//  (*a).b  call member b that foo points to, (read right to left, [*a] = [value pointed to])

/**
* @function empty()
* @abstract Check if object ArrayStack is empty
* @param none
* @return true (is empty) or false (is not empty)
* @pre 
* @post 
**/
template <class T>
bool PointerStack<T>::empty() {
    if (topElement == NULL) {
        return true;
    }
    return false;
}

/**
* @function clear()
* @abstract Clear content of the pointer stack, delete every element
* @param none
* @return
* @pre pointer to filled stack
* @post Empty stack
**/
template <class T>
void PointerStack<T>::clear() {
   while (topElement != NULL){pop(); }
   //delete topElement;//TODO make deconstructor do this?
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
void PointerStack<T>::push(T newItem) {
    node<T>* old_top;
    old_top = topElement;
    
    topElement = new node<T>;
    topElement->next = old_top;
    
    topElement->value = newItem;
}

/**
* @function pop()
* @abstract Remove item from top of the pointer stack
* @param none
* @return
* @pre pointer to first element
* @post pointer to second element and first element deleted
**/
template <class T>
void PointerStack<T>::pop() {
    node<T>* old_top;
    old_top = topElement;
    
    topElement = topElement->next;//TODO crashes if empty (copy code from clear)
    delete old_top;
}

/**
* @function top(topItem)
* @abstract Return item at the top of the stack, give output to user
* @param topItem: the item at the top of the stack
* @return true (succes) or false (something did not work)
* @pre stack of n elements
* @post stack of n elements
**/
template <class T>
void PointerStack<T>::top(T & topItem) {
    topItem = topElement->value;
}

/**
* @function output(ostream & out)
* @abstract Use ostream to give output to user
* @param out: the data to return
* @return output
* @pre input
* @post output
**/

template <class T>
void PointerStack<T>::read() {//TODO not in assaignment should we keep?
    T topItem;
    node<T>* current = topElement;
    if (!empty() ){
        while (current->next != NULL){
            topItem = current->value;
            current = current->next;
            std::cout << topItem << "\n";
        }
    } 
}

#endif
