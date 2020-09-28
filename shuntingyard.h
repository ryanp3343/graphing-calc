#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <iostream>
#include <string>

#include "operator.h"
#include "integer.h"
#include "constants.h"
#include "queue.h"
#include "stack.h"
#include "token.h"
#include "var.h"
#include "cmath"
#include "ctype.h"
#include "TrigFunction.h"



class shuntingyard
{
public:

    shuntingyard()
    {
        userInput();
    }

    void userInput(string str="");

    Queue<Token*> Tokenize();

    Queue<Token*> toPostFix(Queue<Token*> infix);

    Queue<Token*> toRPN()
    {
        //function that uses rpn fucnctions to converts a string to poins
        Queue<Token*> tmp=Tokenize();
        Queue<Token*> user=toPostFix(tmp);
        return user;
    }

    string getExp(){return _expression;}

    double Evaluate(Queue<Token*> postfix, double num);

    void test();

private:

    string _expression;


};

#endif // SHUNTINGYARD_H
