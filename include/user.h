#ifndef USER_H
#define USER_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "constants.h"
#include "shuntingyard.h"
#include "sidebar.h"
#include "input.h"
#include "menu.h"

class user {
public:
    user();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void draw();

    bool mouseIn;
    bool expFlag;
    bool userFlag;
    sf::Cursor cursor;

    float xmin;
    float xmax;
    float grids;

    sf::RenderWindow window;
    sidebar Sidebar;
    input Input;
    sf::RectangleShape userBox;
    std::string userExp;
    sf::Font font;
    sf::Text text;
    sf::Text text2;
    std::string userInput;
    std::string history;
    menu Menu;
    int command;

    static const int TEXT2_SIZE = 16;
    static const int TEXT_SIZE = 25;
    static const sf::Color TEXT_COLOR;
    static const sf::Color TEXT2_COLOR;
};

#endif // USER_H
