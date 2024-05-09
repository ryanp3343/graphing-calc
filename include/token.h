#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>
#include "constants.h"

class Token {
public:
    Token() : _type(-1) {} // Initialize to an invalid type
    virtual ~Token() {}

    Token(const std::string& Tok_str, int type) : _type(type) {}

    virtual void print(std::ostream& outs = std::cout) const {
        outs << "Unknown Token";
    }

    virtual int get_type() const {
        return _type;
    }

    virtual char get_sym() const = 0;
    virtual bool get_trig() const = 0;
    virtual double doTrig(double) const = 0;

    friend std::ostream& operator<<(std::ostream& outs, const Token* n_ptr) {
        n_ptr->print(outs);
        return outs;
    }

protected:
    int _type;
};

#endif // TOKEN_H
