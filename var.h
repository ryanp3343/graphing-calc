#ifndef VAR_H
#define VAR_H

#include "token.h"
#include <iostream>

class var : public Token {
public:
    var() : _var('x') {}
    var(char var) : _var(var) {}

    int get_type() const override {
        return _variable;
    }

    char get_sym() const override {
        return _var;
    }

    bool get_trig() const override {
        return false;
    }

    double doTrig(double) const override {
        return 0.0;
    }

    void print(std::ostream& outs = std::cout) const override {
        outs << _var;
    }

private:
    char _var;
};

#endif // VAR_H