#ifndef TRIGFUNCTION_H
#define TRIGFUNCTION_H

#include "token.h"
#include <cmath>
#include <string>
#include <iostream>
#include <unordered_set>

class TrigFunction : public Token {
public:
    TrigFunction() : trig_function("sin") {} // Set "sin" as the default function
    explicit TrigFunction(const std::string& function) : trig_function(function) {}

    int get_type() const override {
        return TokenTypes::Function;
    }

    char get_sym() const override {
        return 0;
    }

    bool get_trig() const override {
        static const std::unordered_set<std::string> trigFunctions = {
            "sin", "cos", "tan", "csc", "cot", "sec"
        };
        return trigFunctions.count(trig_function) > 0;
    }

    double doTrig(double x) const override {
        if (trig_function == "sin") return std::sin(x);
        if (trig_function == "cos") return std::cos(x);
        if (trig_function == "tan") return std::tan(x);
        if (trig_function == "csc") return 1 / std::sin(x);
        if (trig_function == "cot") return 1 / std::tan(x);
        if (trig_function == "sec") return 1 / std::cos(x);
        return 0.0;
    }

    void print(std::ostream& outs = std::cout) const override {
        outs << trig_function;
    }

private:
    std::string trig_function;
};

#endif // TRIGFUNCTION_H
