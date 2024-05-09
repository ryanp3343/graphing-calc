#ifndef INPUT_H
#define INPUT_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include "constants.h"
#include <string>
#include "shuntingyard.h"

using namespace std;
using namespace sf;

class input {
public:
    explicit input(double xmin, double xmax, double grids);

    void parse(const string& exp);
    void step(int command);
    void getCoordin();
    void getXAx(double x, double y);
    void getYAx(double x, double y);
    void Draw(RenderWindow& window);
    string get_exp() const { return infix; }

    void setXmin(double xmin) { _xmin = xmin; }
    void setXmax(double xmax) { _xmax = xmax; }
    void setGrid(double grids) { _grids = grids; }

private:
    void adjustYCoordinates(double offset); // Add new private helper function
    void adjustScale(double xFactor, double scaleFactor); // Add new private helper function
    void resetGraph(); // Add new private helper function

    RectangleShape _back;
    RectangleShape userBox;
    shuntingyard g;
    Queue<Token*> postfix;
    string infix;
    Text text; // Ensure this matches your existing member variable name
    Font font;
    VertexArray xyCord{ LinesStrip };
    VertexArray xAxis{ LinesStrip };
    VertexArray yAxis{ LinesStrip };

    bool please = false;
    double _xmin;
    double _xmax;
    double _grids;
    double _ypixel;
    double SCALE = 1;
};

#endif // INPUT_H
