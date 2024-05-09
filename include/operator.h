#ifndef OPERATOR_H
#define OPERATOR_H

#include "token.h"
#include <iostream>
#include <cmath>

class Operator : public Token {
public:
    explicit Operator(char op) : _op(op) {}

    ~Operator() override = default; // Virtual destructor

    int get_type() const override {
        return TokenTypes::Operator;
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
            return Precedence::Add;
        case '-':
            return Precedence::Subtract;
        case '/':
            return Precedence::Divide;
        case '*':
            return Precedence::Multiply;
        case '^':
            return Precedence::Exponent;
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
        case '^':
            return std::pow(lhs, rhs); // Use std::pow instead of a manual loop
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
