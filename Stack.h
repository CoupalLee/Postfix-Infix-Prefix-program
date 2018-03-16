#ifndef Stack_h
#define Stack_h

#include <stdio.h>
#include "Node.h"

using namespace std;

template <class TYPE>
class Stack {
private:
    Stack(const Stack &);
    Node<TYPE> *top;
    
public:
    Stack();
    ~Stack();
    void push(const TYPE&);
    TYPE pop( );
    const TYPE& peek( );
    bool isEmpty();
};

#endif /* Stack_h */
