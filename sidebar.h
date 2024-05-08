#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "SFML/Graphics.hpp"
#include "iostream"
#include <string>
#include <vector>
#include "constants.h"
#include "shuntingyard.h"

using namespace sf;


class sidebar
{
public:
    sidebar();
    void draw(RenderWindow& window);
    void set_infix(string infix);

private:
    RectangleShape bar;
    Font font;
    Text expression_txt;
    string history = "";

};
#endif // SIDEBAR_H