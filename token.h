#ifndef TOKEN_H
#define TOKEN_H

#include <string.h>
#include <iostream>
#include "constants.h"

using namespace std;


class Token
{
public:

    Token(){}
    virtual ~Token(){}
    Token(string Tok_str, int type);
    virtual void print(ostream& outs=cout)const {}
    virtual int get_type(){
        return _token;
    }
    virtual char get_sym() {}
    virtual bool get_trig() {}
    virtual double doTrig(double){}
    friend ostream& operator <<(ostream& outs, const Token* n_ptr){
        n_ptr->print(outs);
        return outs;
    }


private:
   int _type;
};


#endif // TOKEN_H
