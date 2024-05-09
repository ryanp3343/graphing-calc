#include "user.h"

const sf::Color user::TEXT_COLOR = sf::Color::Red;
const sf::Color user::TEXT2_COLOR = sf::Color::White;

user::user() : xmin(-10), xmax(10), grids(14), expFlag(false), userFlag(false), Sidebar(), Input(xmin, xmax, grids) {
    // Create window and set framerate limit
    window.create(sf::VideoMode(SFMLWindow::ScreenWidth, SFMLWindow::ScreenHeight), "GRAPHING CALCULATOR");
    window.setFramerateLimit(100);
    mouseIn = true;

    // Load cursor for graphing
    if (cursor.loadFromSystem(sf::Cursor::Hand)) {
        window.setMouseCursor(cursor);
    }

    // Load font for expressions
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Font failed to load" << std::endl;
    }

    // Set the primary text appearance
    text.setFont(font);
    text.setCharacterSize(TEXT_SIZE);
    text.setFillColor(TEXT_COLOR);
    text.setPosition(400, 0);
    text.setStyle(sf::Text::Bold);

    // Set secondary text appearance
    text2.setFont(font);
    text2.setCharacterSize(TEXT2_SIZE);
    text2.setFillColor(TEXT2_COLOR);
    text2.setStyle(sf::Text::Italic);

    // Initialize coordinates and expression display
    Input.getCoordin();
    userExp = Input.get_exp();
    Sidebar.set_infix(userExp);
}

void user::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void user::processEvents() {
    sf::Event event;
    float mouseX, mouseY;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Process keyboard and mouse events
        switch (event.type) {
            // Handle keyboard events
        case sf::Event::KeyPressed:
            switch (event.key.code) {
            case sf::Keyboard::Q:
                window.close();
                break;
            case sf::Keyboard::Right:
                command = Commands::GoRight;
                break;
            case sf::Keyboard::Left:
                command = Commands::GoLeft;
                break;
            case sf::Keyboard::Up:
                command = Commands::GoUp;
                break;
            case sf::Keyboard::Down:
                command = Commands::GoDown;
                break;
            case sf::Keyboard::R:
                command = Commands::Reset;
                break;
            case sf::Keyboard::I:
                command = Commands::ZoomIn;
                break;
            case sf::Keyboard::O:
                command = Commands::ZoomOut;
                break;
            case sf::Keyboard::Space:
                command = Commands::New;
                expFlag = true;
                break;
            case sf::Keyboard::Backspace:
                // Ensure `userInput` is not empty before popping back
                if (!userInput.empty()) {
                    userInput.pop_back();
                    text.setString(userInput);
                    userFlag = true;
                }
                break;

            case sf::Keyboard::Enter:
                Input.parse(userInput);
                history += (userInput + '\n');
                Sidebar.set_infix(history);
                Input.getCoordin();
                command = Commands::Delete;
                expFlag = false;
                userFlag = false;
                userInput = "";
                break;
            }
            break;

            // Process text input
        case sf::Event::TextEntered:
            if (expFlag) {
                // Only add printable characters (excluding backspace)
                if (event.text.unicode >= 32 && event.text.unicode < 127) {
                    userInput += static_cast<char>(event.text.unicode);
                    text.setString(userInput);
                    userFlag = true;
                }
            }
            break;


            // Update the cursor type based on location
        case sf::Event::MouseMoved:
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
            if (mouseX >= SFMLWindow::GraphPanel && mouseX <= SFMLWindow::ScreenWidth) {
                cursor.loadFromSystem(sf::Cursor::Text) ? window.setMouseCursor(cursor) : void();
            }
            else {
                cursor.loadFromSystem(sf::Cursor::Hand) ? window.setMouseCursor(cursor) : void();
            }
            break;

        default:
            break;
        }
    }
}

void user::update() {
    // Update the input based on the current command
    Input.step(command);
    command = 0;
}

void user::render() {
    window.clear();
    draw();
    if (userFlag) {
        window.draw(text);
        window.draw(text2);
    }
    window.display();
}

void user::draw() {
    Input.Draw(window);
    Sidebar.draw(window);
    Menu.draw(window);
}
