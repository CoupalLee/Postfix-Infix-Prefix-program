#include <stdio.h>
#include <string>
#include "Expression.h"

using namespace std;

//constructor that is given which one type it is( prefix postfix or infix )
Expression::Expression (string input, int direction) {
    this->input = input;
    switch (direction) {
        case 1:  infix = input;
        case 2:  postfix = input;
        case 3:  prefix = input;
    }
}

string Expression::inToPostFix() {
    string input = getInput();
    Stack<char> operatorStack;
    string post = "";
    for(int i = 0;i< input.length();i++) {
        if(isOperator(input[i])) //when you reach an operator
        {
            while(!operatorStack.isEmpty() && operatorStack.peek() != '(' && hasHigherPrecedence(operatorStack.peek(),input[i]))
            { //and the stack is not empty and it respects the right operator that comes first AKA when there are no parentheses
                post+= operatorStack.peek(); //add the operator to the final answer
                operatorStack.pop(); // pop it
            }
            operatorStack.push(input[i]);//push it onto the stack of operators
        }
        else if(isOperand(input[i]))
        {
            post +=input[i];//when you reach an operand add it to the final answer
        }
        
        else if (input[i] == '(') // when you reach an open bracket put that into the stack of operators
        {
            operatorStack.push(input[i]); // this will be used to recongize which operator to pop
        }
        
        else if(input[i] == ')')
        {
            while(!operatorStack.isEmpty() && operatorStack.peek() !=  '(') {
                //search the stack until you reach the most recently placed operator to pop out
                post += operatorStack.peek();
                operatorStack.pop(); //pop the operator
            }
            operatorStack.pop(); //and its following bracket
        }
    }
    
    while(!operatorStack.isEmpty()) {
        post += operatorStack.peek(); //any remaining operators also need to be popped
        operatorStack.pop();
    }
    postfix = post; //lastly you have your answer
    return post;
}


string Expression::inToPreFix() {
    string infix = getInput();
    //create new stack
    Stack<char> s;
    //go through array of string right to left
    for(long i = infix.size()-1; i >=0 ;i--){
        
        //if (infix[i] == ' ' || infix[i] == ',') continue;
        if(isOperator(infix[i])){
            //while precedence is lower/equal to
            while(!s.isEmpty() && s.peek() != ')' && getWeightOfPrecedence(infix[i])<= getWeightOfPrecedence(s.peek())){
                //add top to prefix & pop
                prefix += s.peek();
                s.pop();
            }//end while
            
            //push operator on stack
            s.push(infix[i]);
        }//end if
        //if operand, add to prefix str
        if(isOperand(infix[i])){
            prefix += infix[i];
        }
        //if ch, is ')', push to stack
        if(infix[i] == ')'){
            s.push(infix[i]);
        }
        //if ch is '('
        if (infix[i] == '('){
            //while stack top is not corresp. ')'
            while(!s.isEmpty() && s.peek() != ')'){
                //pop op, and add to prefix str
                prefix += s.peek();
                s.pop();
            }//end while
            s.pop();
        }
    }
    //pop remaining opeators
    while(!s.isEmpty()){
        prefix += s.peek();
        s.pop();
    }
    string temp;
    //reverse string to form prefix
    for (long i=prefix.size()-1; i>=0; i--){
        temp += prefix[i];
    }
    //return prefix
    int numx= (int)(prefix.size()/2)-1;
    prefix = temp;
    prefix = prefix.substr(0,numx);
    this->prefix = prefix;
    return prefix;
}


string Expression::postToInFix() {
    string postfix = getPostFix(); // create a new string postfix
    Stack<string> stackOfOperands;
    string temp;
    int length = (int)postfix.size();
    
    for (int i = 0; i <= length; i++) { //go through the entire array
        
        if (isOperator(postfix[i])) {//when you reach an operator
            string operand1 = stackOfOperands.peek(); //store operand 1 and 2 into a string
            stackOfOperands.pop();
            string operand2 = stackOfOperands.peek();
            stackOfOperands.pop();
            temp = "(" + operand2 + prefix[i] + operand1 + ")"; //concatinate the two operands and the operator
            stackOfOperands.push(temp); // push the newly made postFix expression (A+B) into the stack
        }
        
        else {
            stackOfOperands.push(string (1, postfix[i])); //when you reach an operand add it to the stack
        }
    }
    infix = temp;
    return temp;
}


string Expression::preToInFix() {
    string prefix = getPreFix();
    Stack<string> stackOfOperands;
    
    int length = (int)prefix.size();
    
    for (int i = length; i >= 0; i--) {
        //start at the back of the prefix expression and store the first few operands in the
        // stack
        if (isOperator(prefix[i])) {
            //when you reach an operator
            string operand1 = stackOfOperands.peek(); //get the first operand
            stackOfOperands.pop(); //remove it from the stack
            string operand2 = stackOfOperands.peek(); // get the second operand
            stackOfOperands.pop(); //remove it from the stack
            string temp = "(" + operand1 + prefix[i] + operand2 + ")";
            //store the operands and operator in the form (A*B)
            stackOfOperands.push(temp); // put that evaluated expression (A*B) back into
            // the stack of operands
        }
        else {
            //when you reach an operand store it into the stack of operands.
            stackOfOperands.push(string(1, prefix[i]));
        }
    }
    prefix = stackOfOperands.peek();
    return stackOfOperands.peek(); // by the end of the loop it should be one big
    // operand that you can just return!
}


double Expression::evaluate() {
    
    Stack<char> stackOfOperands;
    string pref = getPreFix();
    //double answer = 0;
    //char operandOne;
    //char operandTwo;
    
    Stack<char> stk;
    
    for(int i = 0; i < pref.length(); i++)
        stk.push(pref.at(i));
    
    int length = (int)pref.size();
    
    for (int i = length; i >= 0; i--) {
        if(isOperator(pref[i])){
            //double operand1 = convertToDoub(stackOfOperands.peek());
            stackOfOperands.pop();
            // double operand2 = convertToDoub(stackOfOperands.peek());
            stackOfOperands.pop();
        }
        else{
            stackOfOperands.push(stk.peek());
            stk.pop();
        }
    }
    
    // Hello Marker;
    // The idea here was to do something similar to converting to infix.
    // We start by sorting the operators and operands
    // when you reach an operator you convert and store the operands to numbers and store that back into a number stack
    // repeat until the end of the array
    // There is an issue with calling convertToDoub that we have never seen
    //Linker command failed with exit code 1
    // it refrences only the two lines where we use converToDoub
    // otherwise this evaluate method would be complete.
    // :feelsbadman:
    
    
    
    return 1.0;
    
}

bool Expression::isOperator(char inputCharacter) { //return true if any of the operators below are the char given
    if(inputCharacter == '+'||
       inputCharacter == '-' ||
       inputCharacter == '*' ||
       inputCharacter == '/' ||
       inputCharacter == '^' ||
       inputCharacter == '$')
        return true;
    
    return false;
}
double convertToDoub(char x){
    double re;
    switch(x){
        case '0':re= 0.0;break;
        case '1':re= 1.0;break;
        case '2':re= 2.0;break;
        case '3':re= 3.0;break;
        case '4':re= 4.0;break;
        case '5':re= 5.0;break;
        case '6':re= 6.0;break;
        case '7':re= 7.0;break;
        case '8':re= 8.0;break;
        case '9':re= 9.0;break;
        default:re = 0.0;break;
    }
    return re;
}


int Expression::getWeightOfPrecedence(char inputOperator) {
    int weight = -1;
    //this method demonstrates PEMDAS
    switch(inputOperator)
    {
        case '+':
        case '-':
            weight = 1; //if + or - then the precendence is low
        case '*':
        case '/':
            weight = 2; // if * or / then higher precedence
        case '^':
            weight = 3;
        case '$':
            weight = 4;
    }
    return weight;
}

int Expression::hasHigherPrecedence(char op1, char op2)
{ //compare the two precendences and return the larger one
    int op1Weight = getWeightOfPrecedence(op1);
    int op2Weight = getWeightOfPrecedence(op2);
    
    if(op1Weight == op2Weight)
    {
        if(isRightAssociative(op1))
            return false;
        else
            return true;
    }
    return op1Weight > op2Weight ?  true: false;
}

bool Expression::isOperand(char input)
{//return true if it is a number between 0 and 9 or letter upercase
    //or lowercase A to Z.
    if(input >= '0' && input <= '9')
        return true;
    if(input >= 'a' && input <= 'z')
        return true;
    if(input >= 'A' && input <= 'Z')
        return true;
    return false;
}

int Expression::isRightAssociative(char op)
{
    if(op == '$') return true;
    return false;
}

//getters for Prefix and Infix and Postfix and Input
string Expression::getInput() { //done
    return input;
}

string Expression::getPreFix(){ //done
    return prefix;
}

string Expression::getPostFix(){ //done
    return postfix;
}

string Expression::getInFix(){ //done
    return infix;
}

string Expression::getValue(){ //done
    string value;
    return value;
}

