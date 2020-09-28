#ifndef INTEGER_H
#define INTEGER_H


#include "token.h"
#include "constants.h"
#include <iostream>

using namespace std;

class Integer: public Token
{
public:
    Integer(double num)
    {
        _num=num;
    }
    int get_type()
    {
        return _int;
    }
    double get_Num(){

        return _num;
    }
    void print(ostream& outs=cout)const{
        outs<<_num;

    }

private:
    double _num;

};

#endif // INTEGER_H
