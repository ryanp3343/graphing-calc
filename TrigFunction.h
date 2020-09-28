#ifndef TRIGFUNCTION_H
#define TRIGFUNCTION_H

#include "constants.h"
#include "cmath"
#include "token.h"
#include <iostream>

class TrigFunction: public Token
{
public:
    TrigFunction()
    {
        trig_function=" ";
    }
    TrigFunction(string function)
    {
        trig_function=function;
    }
    int get_type()
    {
        return _function;
    }
    string name()
    {
        return trig_function;
    }

    void print(ostream& outs = cout)const{
        outs<<trig_function;
    }

    bool get_trig()
    {
        //if the token is a trig function return true
       if(trig_function=="sin" || trig_function=="cos"|| trig_function=="tan")
       {
           return true;
       }
       if(trig_function=="csc" || trig_function=="cot" || trig_function=="sec")
       {
           return true;
       }
       else
           return false;
    }

    double doTrig(double x){

        //uses cmath to evaluate trig functions
        if(trig_function=="sin")
            return sin(x);
        else if(trig_function=="cos")
            return cos(x);
        else if(trig_function=="tan")
            return tan(x);
        else if(trig_function=="csc")
            return (1/(sin(x)));
        else if(trig_function=="cot")
            return (1/(tan(x)));
        else if(trig_function=="sec")
            return (1/(cos(x)));
        else if(trig_function=="sqrt")
            return sqrt(x);
    }
private:
    string trig_function;
};

#endif // TRIGFUNCTION_H
