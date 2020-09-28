#ifndef INPUT_H
#define INPUT_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include "constants.h"
#include <string>
#include "shuntingyard.h"
using namespace std;
using namespace sf;

class input
{
public:
    //intialize shunting yard object to get postfix expression
    input(double xmin,double xmax,double grids): g(), postfix(g.toRPN()), _xmin(xmin),_xmax(xmax), _grids(grids)
    {
        //set x y axis to lines and graph line to points

        xyCord.setPrimitiveType(LinesStrip);
        xAxis.setPrimitiveType(LinesStrip);
        yAxis.setPrimitiveType(LinesStrip);

        //gets expression from shunting yard to process
        infix=g.getExp();
        //set backround color position and size
        _back.setFillColor(Color(0,0,0));
        _back.setPosition(0,0);
        _back.setSize(Vector2f(GRAPH_PANEl,SCREEN_HEIGHT));
        //set user input box color size and pos
        userBox.setFillColor(Color(105,105,105));
        userBox.setPosition(400,0);
        userBox.setSize(Vector2f(300,50));

    }

    void parse(string exp)
    {
        //used to parse input from screen and sent to shunting yard
        g.userInput(exp);
        postfix=g.toRPN();
    }

    void step(int command);

    void getCoordin();

    void getXAx(double x, double y);

    void getYAx(double x, double y);

    void Draw(RenderWindow& window);

    string get_exp(){return infix;}

    void setXmin(double xmin){_xmin=xmin;}
    void setXmax(double xmax){_xmax=xmax;}
    void setGrid(double grids){_grids=grids;}

private:

    RectangleShape _back;
    RectangleShape userBox;
    shuntingyard g;
    Queue<Token*> postfix;
    string infix;
    Text text;
    Font font;
    VertexArray xyCord;
    VertexArray xAxis;
    VertexArray yAxis;

    bool please=false;

    double _xmin;
    double _xmax;
    double _grids;
    double _ypixel;
    double SCALE=1;
};

#endif // INPUT_H
