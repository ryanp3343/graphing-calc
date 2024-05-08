#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>
#include "constants.h"

using namespace std;

class Token
{
public:
    Token() {}
    virtual ~Token() {}
    Token(string Tok_str, int type) : _type(type) {}

    virtual void print(ostream& outs = cout) const {}
    virtual int get_type() const {
        return _type;
    }
    virtual char get_sym() const = 0;
    virtual bool get_trig() const = 0;
    virtual double doTrig(double) const = 0;

    friend ostream& operator <<(ostream& outs, const Token* n_ptr) {
        n_ptr->print(outs);
        return outs;
    }

private:
    int _type;
};

#endif // TOKEN_H