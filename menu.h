#ifndef MENU_H
#define MENU_H


#include "SFML/Graphics.hpp"
#include "iostream"
#include <string>
#include <vector>
#include "constants.h"
#include "shuntingyard.h"

using namespace std;
using namespace sf;

class menu
{
public:
    menu();
    void draw(RenderWindow& window);

private:
    Text text;
    Font font;
};

#endif // MENU_H
