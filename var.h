#ifndef VAR_H
#define VAR_H
#include <iostream>
#include "token.h"

class var: public Token{

public:
    var()
    {
        _var='x';
    }
    var(char var)
    {
        _var=var;
    }
    int get_type()
    {
        return _variable;
    }
    char get_var()
    {
        return _var;
    }
    void print(ostream& outs = cout)const{
        outs<<_var;
    }


private:
    char _var;
};

#endif // VAR_H
