#include "Stack.h"
#include <assert.h>

using namespace std;

//Constructor
template <class TYPE>
Stack<TYPE>::Stack(){
    top = NULL;
    
}
//Destructor
template <class TYPE>
Stack<TYPE>::~Stack(){
    Node<TYPE> *nodePtr, *nextNode;
    //Position nodePtr at the top of the stack.
    nodePtr = top;
    
    // Traverse the list deleting each node.
    while (nodePtr != NULL)
    {
        nextNode = nodePtr->next;
        delete nodePtr;
        nodePtr = nextNode;
    }
}
//Put item on top of stack
template <class TYPE>
void Stack<TYPE>::push(const TYPE& e){
    top=new Node<TYPE>(e, top);
}

//Take item from top of stack
template <class TYPE>
TYPE Stack<TYPE>::pop(){
    Node<TYPE> *temp=top;        // Temporary pointer
    assert(!isEmpty());          // First make sure the stack isn't empty.
    TYPE data=top->value;
    top = top->next;
    delete temp;
    return data;
}

//Peek at top of stack
template <class TYPE>
const TYPE& Stack<TYPE>::peek(){
    assert(!isEmpty());
    return top->value; //return the top value of the stap
}

//True if stack is empty
template <class TYPE>
bool Stack<TYPE>::isEmpty(){
    return (top == NULL);
}
