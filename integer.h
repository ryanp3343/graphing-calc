#ifndef INTEGER_H
#define INTEGER_H

#include "token.h"
#include "constants.h"
#include <iostream>

class Integer : public Token {
public:
    Integer(double num) : _num(num) {}

    int get_type() const override {
        return _int;
    }

    char get_sym() const override {
        return 0;
    }

    bool get_trig() const override {
        return false;
    }

    double doTrig(double) const override {
        return 0.0;
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