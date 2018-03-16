
#ifndef Node_h
#define Node_h

using namespace std;

template <class TYPE> class Stack;
template <class TYPE>
class Node{
    friend class Stack<TYPE>;
    TYPE value;
    Node<TYPE> * next;
    Node (const  TYPE& t,  Node * n = NULL){
        value = t;
        next = n;
    }
};


#endif /* Node_h */
