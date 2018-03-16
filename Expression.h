#ifndef Expression_h
#define Expression_h

#include "Node.h"
#include "Stack.h"

using namespace std;

class Expression {
private:
    string infix;
    string postfix;
    string prefix;
    int value;
    string input;
    
public:
    Expression (string input, int direction);
    string getInput();
    string getPreFix();
    string getPostFix();
    string getInFix();
    string inToPostFix ();
    string inToPreFix ();
    string postToInFix ();
    string preToInFix ();
    string getValue();
    double convertToDoub(char x);
    int isRightAssociative(char input);
    bool isOperand(char input);
    bool isOperator(char inputCharacter);
    int hasHigherPrecedence(char firstCharacter, char secondCharacter);
    int getWeightOfPrecedence(char inputOperator);
    double evaluate ();
};
#endif /* Expression_h */
