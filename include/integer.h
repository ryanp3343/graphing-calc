#ifndef INTEGER_H
#define INTEGER_H

#include "token.h"
#include "constants.h"
#include <iostream>

class Integer : public Token {
public:
    explicit Integer(double num = 0.0) : _num(num) {}

    int get_type() const override {
        return TokenTypes::Integer;
    }

    char get_sym() const override {
        return 0; // Default symbol when not applicable
    }

    bool get_trig() const override {
        return false;
    }

    double doTrig(double) const override {
        return 0.0; // Not applicable for integers
    }

    double get_Num() const {
        return _num;
    }

    void print(std::ostream& outs = std::cout) const override {
        outs << _num;
    }

private:
    double _num;
};

#endif // INTEGER_H
