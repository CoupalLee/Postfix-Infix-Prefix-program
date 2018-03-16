#include <stdio.h>
#include <iostream>
#include <string>
#include "Expression.h"


using namespace std;

int main(){
    
    string tempString = "";
    int direction = -1;
    while(true && direction !=0) {
        cout << "What is your expression type? (Enter integer) Or enter 0 to quit" << endl;
        //based on user input determine the type of expression
        cout << "1) Infix" << endl;
        cout << "2) Postfix" << endl;
        cout << "3) Prefix" << endl;
        cin >> direction;
        if(direction == 0)
            break;
        cout << "Enter your expression : ";
        cin >> tempString;
        
        Expression expression(tempString,direction);
        
        switch (direction) {
            case 1:
                // if infix give postfix and prefix and evaluate
                cout << "Postfix : " << expression.inToPostFix() << endl;
                cout << "Prefix : " << expression.inToPreFix() << endl;
                cout<< "evaluated : "<<expression.evaluate()<<endl;
                break;
            case 2:
                // if postfix give infix and prefix and evaluate
                cout << "Infix : " << expression.postToInFix() << endl;
                cout << "Prefix : " << expression.inToPreFix()<< endl;
                cout<< "evaluated : "<<expression.evaluate()<<endl;
                break;
            case 3:
                // if prefix give postfix and infix and evaluate
                cout << "Infix : "<< expression.preToInFix() << endl;
                cout << "Postfix : " <<expression.inToPostFix() << endl;
                cout<< "evaluated : "<<expression.evaluate()<<endl;
                break;
            default:
                break;
        }
        
    }
    return 0;
}


