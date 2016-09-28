/**
* Class name: Boom, stack implemented using a singly connected list
* @author Lisa Pothoven (s1328263)
* @author David Kleingeld (s1432982)
* @file Boom.h
* @date 20-09-2016
**/


#ifndef Boom_h
#define Boom_h

struct Leaf {
  leaf* left right;
  enum { PLUS, MINUS, NUMBER, VARIABLE } type;
  union{
    char variable;
    double number;
  };
}

class Boom {
public:
  /**
  * @function Boom()
  * @abstract Constructor: Create new object node
  * @param
  * @return object of class node
  * @pre 
  * @post 
  **/
  Boom();
  /**
  * @function ~Boom()
  * @abstract Deconstructor: Deletes tree
  * @param
  * @return object of class node
  * @pre 
  * @post 
  **/
  ~Boom();
  /**
  * @function empty()
  * @abstract Check if object Boom is empty
  * @param
  * @return true (is empty) or false (is not empty)
  * @pre 
  * @post 
  **/
private:
  root;//stores the highest element in the stack
};


#endif
