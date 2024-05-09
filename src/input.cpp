#include "input.h"

input::input(double xmin, double xmax, double grids)
    : g(), postfix(g.toRPN()), _xmin(xmin), _xmax(xmax), _grids(grids) {
    _back.setFillColor(Color(0, 0, 0));
    _back.setPosition(0, 0);
    _back.setSize(Vector2f(SFMLWindow::GraphPanel, SFMLWindow::ScreenHeight));

    userBox.setFillColor(Color(105, 105, 105));
    userBox.setPosition(400, 0);
    userBox.setSize(Vector2f(300, 50));

    if (!font.loadFromFile("arial.ttf")) {
        cout << "Font failed to load. Check the absolute path." << endl;
        cin.get();
        exit(-1);
    }

    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(Color::Black);
    text.setStyle(Text::Bold);
}

void input::parse(const string& exp) {
    g.userInput(exp);
    postfix = g.toRPN();
}

void input::getXAx(double x, double y) {
    xAxis.clear();
    Vertex xVertex[2];
    xVertex[0].position = Vector2f(0, y);
    xVertex[0].color = Color(255, 255, 255);
    xAxis.append(xVertex[0]);

    xVertex[1].position = Vector2f(SFMLWindow::GraphPanel, y);
    xVertex[1].color = Color(255, 255, 255);
    xAxis.append(xVertex[1]);
}

void input::getCoordin() {
    xyCord.clear();
    double range = _xmax - _xmin;
    double prevX = std::numeric_limits<double>::quiet_NaN();
    double prevY = std::numeric_limits<double>::quiet_NaN();

    for (double xpix = 0; xpix <= SFMLWindow::GraphPanel; ++xpix) {
        double xval = _xmin + (xpix / SFMLWindow::GraphPanel) * range;
        double yval = g.Evaluate(postfix, xval) * SCALE;
        _ypixel = (1 - (yval / _grids)) * SFMLWindow::ScreenHeight / 2;

        if (!std::isnan(prevX) && prevX <= 0 && xval >= 0) {
            getYAx(xpix, _ypixel);
        }

        if (!std::isnan(prevY) && prevY <= 0 && yval >= 0) {
            getXAx(xpix, _ypixel);
        }

        Vertex vertex;
        vertex.position = Vector2f(xpix, _ypixel);
        vertex.color = Color(58, 185, 54);
        xyCord.append(vertex);

        prevX = xval;
        prevY = yval;
    }
}

void input::getYAx(double x, double y) {
    yAxis.clear();
    Vertex yVertex[2];
    yVertex[0].position = Vector2f(x, 0);
    yVertex[0].color = Color(255, 255, 255);
    yAxis.append(yVertex[0]);

    yVertex[1].position = Vector2f(x, SFMLWindow::ScreenHeight);
    yVertex[1].color = Color(255, 255, 255);
    yAxis.append(yVertex[1]);
}

void input::step(int command) {
    switch (command) {
    case Commands::GoRight:
        setXmax(_xmax + 1);
        setXmin(_xmin + 1);
        break;
    case Commands::GoLeft:
        setXmin(_xmin - 1);
        setXmax(_xmax - 1);
        break;
    case Commands::GoUp:
        adjustYCoordinates(100);
        break;
    case Commands::GoDown:
        adjustYCoordinates(-100);
        break;
    case Commands::ZoomIn:
        adjustScale(0.95, 1.05);
        break;
    case Commands::ZoomOut:
        adjustScale(1.05, 0.95);
        break;
    case Commands::Reset:
        resetGraph();
        break;
    case Commands::New:
        please = true;
        break;
    case Commands::Delete:
        please = false;
        break;
    default:
        break;
    }
    getCoordin();
}

void input::adjustYCoordinates(double offset) {
    for (size_t i = 0; i < xyCord.getVertexCount(); ++i) {
        xyCord[i].position.y += offset;
    }
    xAxis.clear();
    getXAx(0, xAxis[0].position.y + offset);
}

void input::adjustScale(double xFactor, double scaleFactor) {
    setXmin(_xmin * xFactor);
    setXmax(_xmax * xFactor);
    SCALE *= scaleFactor;
}

void input::resetGraph() {
    setXmax(10);
    setXmin(-10);
    SCALE = 1;
    getCoordin();
}

void input::Draw(RenderWindow& window) {
    window.clear();
    window.draw(_back);
    window.draw(yAxis);
    window.draw(xAxis);
    window.draw(xyCord);
    if (please) {
        window.draw(userBox);
    }
}
