#ifndef OPERATOR_H
#define OPERATOR_H

#include "token.h"
#include <iostream>
#include <cmath>

class Operator : public Token {
public:
    Operator(char op) : _op(op) {}

    int get_type() const override {
        return _operator;
    }

    char get_sym() const override {
        return _op;
    }

    bool get_trig() const override {
        return false;
    }

    double doTrig(double) const override {
        return 0.0;
    }

    int prec() const {
        switch (_op) {
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

    double calc_op(double lhs, double rhs) const {
        switch (_op) {
        case '+':
            return lhs + rhs;
        case '-':
            return lhs - rhs;
        case '*':
            return lhs * rhs;
        case '/':
            return lhs / rhs;
        case '^': {
            double result = 1;
            for (int i = 0; i < rhs; i++) {
                result *= lhs;
            }
            return result;
        }
        default:
            return 0;
        }
    }

    void print(std::ostream& outs = std::cout) const override {
        outs << _op;
    }

private:
    char _op;
};

#endif // OPERATOR_H