#include "sidebar.h"

sidebar::sidebar()
{
    //set the side bars color position and size
    bar.setFillColor(Color(100, 100, 100));
    bar.setPosition(Vector2f(SFMLWindow::GraphPanel, 0));
    bar.setSize(Vector2f(SFMLWindow::SideBar, SFMLWindow::ScreenHeight));

    //load text for expression on the side bard
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Sidebar: Font failed to load. Check absolute path." << std::endl;
        std::cin.get();
        exit(-1);
    }
    
    history_label.setFont(font);
    history_label.setCharacterSize(30);
    history_label.setFillColor(Color::White);
    history_label.setStyle(Text::Bold);
    history_label.setString("History");

    //FloatRect label_bounds = history_label.getLocalBounds();
    //history_label.setOrigin(label_bounds.width / 2, label_bounds.height / 2);
    history_label.setPosition(SFMLWindow::GraphPanel + 10, 10);

    underline.setSize(Vector2f(SFMLWindow::SideBar - 10, 3));
    underline.setFillColor(Color::White);
    underline.setPosition(SFMLWindow::GraphPanel + 5, 60);

    expression_txt.setFont(font);
    expression_txt.setCharacterSize(25);
    expression_txt.setFillColor(Color::White);
    expression_txt.setStyle(Text::Bold);

}

void sidebar::draw(RenderWindow& window)
{
    //draws sidebar
    window.draw(bar);
    window.draw(history_label);
    window.draw(underline);

    float height = 70;
    //sets position of expression to go on the bar
    expression_txt.setPosition(Vector2f(SFMLWindow::GraphPanel + 2, height));
    //draws expression text on sidebar
    window.draw(expression_txt);
}

void sidebar::set_infix(std::string infix)
{
    //sets the string to be printed on the sidebar
    expression_txt.setString(infix);
}