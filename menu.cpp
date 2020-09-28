#include "menu.h"

menu::menu()
{
    if (!font.loadFromFile("arial.ttf"))
    {
           cout<<"ERROR";
           exit(-1);
    }
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(Color::White);
    text.setStyle(Text::Italic);
}

void menu::draw(RenderWindow &window)
{
    text.setPosition(0,0);
    text.setString("[Up]: Move Up");
    window.draw(text);
    text.setPosition(0,18);
    text.setString("[Down]: Move Down");
    window.draw(text);
    text.setPosition(0,36);
    text.setString("[Left]: Move Left");
    window.draw(text);
    text.setPosition(0,54);
    text.setString("[Right]: Move Right");
    window.draw(text);
    text.setPosition(0,72);
    text.setString("[Space]: New Expression");
    window.draw(text);
    text.setPosition(GRAPH_PANEl-61,0);
    text.setString("[Q]: Exit");
    window.draw(text);
    text.setPosition(GRAPH_PANEl-84,18);
    text.setString("[I]: Zoom In");
    window.draw(text);
    text.setPosition(GRAPH_PANEl-105,36);
    text.setString("[O]: Zoom Out");
    window.draw(text);
    text.setPosition(GRAPH_PANEl-77,54);
    text.setString("[R]: Reset");
    window.draw(text);



}
