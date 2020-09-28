#include "sidebar.h"

sidebar::sidebar()
{
    //set the side bars color position and size
    bar.setFillColor(Color(25,30,32));
    bar.setPosition(Vector2f(GRAPH_PANEl,0));
    bar.setSize(Vector2f(SIDE_BAR, SCREEN_HEIGHT));

    //load text for expression on the side bard
    if (!font.loadFromFile("arial.ttf")){
           cout<<"Sidebar: Font failed to load. Check absolute path."<<endl;
           cin.get();
           exit(-1);
       }
   //set font size color and style for the expression text
   expression_txt.setFont(font);
   expression_txt.setCharacterSize(25);
   expression_txt.setFillColor(Color::Black);
   expression_txt.setStyle(Text::Bold);

}

void sidebar::draw(RenderWindow &window)
{
    //draws sidebar
    window.draw(bar);

    float height=10;
    //sets position of expression to go on the bar
    expression_txt.setPosition(Vector2f(GRAPH_PANEl+2,height));
    //draws expression text on sidebar
    window.draw(expression_txt);
}

void sidebar::set_infix(string infix)
{
    //sets the string to be printed on the sidebar
    expression_txt.setString(infix);
}
