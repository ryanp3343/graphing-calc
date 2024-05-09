#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "constants.h"

class menu {
public:
    menu();
    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    std::vector<std::string> options;
    sf::Text text;

    // Constants for text appearance
    static const int CHARACTER_SIZE = 16;
    static const sf::Color TEXT_COLOR;
    static const sf::Uint32 TEXT_STYLE = sf::Text::Italic;
};

#endif // MENU_H
