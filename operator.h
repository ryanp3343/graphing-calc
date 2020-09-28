#ifndef OPERATOR_H
#define OPERATOR_H

#include "token.h"
#include "constants.h"
#include <iostream>
#include <math.h>

using namespace std;

class Operator: public Token
{
public:
    Operator(char op): _op(op) {}

    int get_type()
    {
        return _operator;
    }
    //returns precedence of operators for comparison
    int prec()
    {
        switch(this->get_sym())
        {
        case '+':
            return add;

        case '-':
            return sub;

        case '/':
            return divide;

        case '*':
            return mult;

        case '^':
            return expon;

        default:
            return -1;
        }

    }
    char getOp()
    {
        return _op;
    }
    char setOp(char op)
    {
        _op=op;
        return op;
    }

    char get_sym()
    {
        return _op;
    }

    //how to calculate when with certain operators
    double calc_op(double lhs, double rhs)
    {
        if(_op=='+')
        {
            return (lhs+rhs);
        }
        else if(_op=='-')
        {
            return (lhs-rhs);
        }
        else if(_op=='*')
        {
            return (lhs*rhs);
        }
        else if(_op=='/')
        {
            return (lhs/rhs);
        }
        else if(_op=='^')
        {
            double result = 1;
            for(int i=0; i<rhs; i++)
            {
                result*=lhs;
            }
            return result;
        }
    }

    void print(ostream& outs=cout)const{
        outs<<_op;
    }

private:
    int _precedence;
    char _op;
};

#endif // OPERATOR_H
