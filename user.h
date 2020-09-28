#ifndef USER_H
#define USER_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include "constants.h"
#include "shuntingyard.h"
#include "sidebar.h"
#include "input.h"
#include "menu.h"


using namespace sf;

class user
{
public:
    user();
    void run();
    void update();
    void processEvents();
    void render();
    void draw();

private:
    bool mouseIn;
    Cursor cursor;
    float xmin;
    float xmax;
    float grids;

    RenderWindow window;
    sidebar Sidebar;
    input Input;
    RectangleShape userBox;
    string userExp;
    Font font;
    Text text;
    Text text2;
    string userInput;
    string history;
    menu Menu;
    int command;
};



#endif // USER_H
