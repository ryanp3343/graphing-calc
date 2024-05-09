#include "menu.h"

const sf::Color menu::TEXT_COLOR = sf::Color::White;

menu::menu() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Could not load font 'arial.ttf'" << std::endl;
    }

    text.setFont(font);
    text.setCharacterSize(CHARACTER_SIZE);
    text.setFillColor(TEXT_COLOR);
    text.setStyle(TEXT_STYLE);

    options = {
        "[Up]: Move Up",
        "[Down]: Move Down",
        "[Left]: Move Left",
        "[Right]: Move Right",
        "[Space]: New Expression",
        "[Q]: Exit",
        "[I]: Zoom In",
        "[O]: Zoom Out",
        "[R]: Reset"
    };
}

void menu::draw(sf::RenderWindow& window) {
    float yOffset = 0;
    const float yIncrement = 18;

    for (const auto& option : options) {
        text.setPosition(0, yOffset);
        text.setString(option);
        window.draw(text);
        yOffset += yIncrement;
    }

    const float graphPanelOffsetX = SFMLWindow::GraphPanel - 61;

    text.setPosition(graphPanelOffsetX, 0);
    text.setString("[Q]: Exit");
    window.draw(text);

    text.setPosition(graphPanelOffsetX - 23, 18);
    text.setString("[I]: Zoom In");
    window.draw(text);

    text.setPosition(graphPanelOffsetX - 44, 36);
    text.setString("[O]: Zoom Out");
    window.draw(text);

    text.setPosition(graphPanelOffsetX - 16, 54);
    text.setString("[R]: Reset");
    window.draw(text);
}
