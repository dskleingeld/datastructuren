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
class node {
public:
    node* next;
    T value;
};


template <class T>
class pointerStack {
public:
    pointerStack();
    node* startNew();
    bool isEmpty();
    void clear();
    void push(T newItem);
    void pop();
    void top(T & topItem);
//protected:
    //void output(ostream & out, T data);
	void read();
private:
    // Array of certain size
    node* top;//stores the highest element in the stack
};

/**
* @function ArrayStack()
* @abstract Constructor: Create new object node
* @param
* @return 
* @pre 
* @post 
**/
template <class T>
pointerStack<T>::pointerStack() {
    top = new node
    top.next = NULL;
}

/**
* @function push()
* @abstract Add newItem to top of the stack
* @param newItem: new item to be added to the stack
* @return
* @pre stack of n elements
* @post stack of n+1 elements
**/
template <class T>
void pointerStack<T>::push(T newItem) {
    old_top = top;
    
    top = new node;
    top.next = old_top;
    
    top.value = newItem;
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
void pointerStack<T>::pop() {
    old_top = top;
    
    top = top.next
    delete old_top;
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
void pointerStack<T>::clear() {//TODO make the deconstructor call this
   while (top != NULL){pop(); }
   delete top;
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
void pointerStack<T>::top(T & topItem) {
    topItem = top.value;
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
void ArrayStack<T>::output(ostream & out, T data) {
    out << data;
}*/

template <class T>
void ArrayStack<T>::read() {
    T topItem;
    node* next = top;
    while (next != NULL){
        topItem = next.value;
        next = next.next;
        std::cout << topItem;
    }
    topItem = next.value;
    std::cout << topItem;

#endif
