#include "user.h"

bool expFlag = false;
bool userFlag = false;

//intialize domain sidebr and input class

user::user() : xmin(-10), xmax(10), grids(14), Sidebar(), Input(xmin, xmax, grids)
{

    //create window and frame limit
    window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GRAPHING CALCULATOR");
    window.setFramerateLimit(100);
    mouseIn = true;
    //hand cursor for graph
    if (cursor.loadFromSystem(sf::Cursor::Hand))
    {
        window.setMouseCursor(cursor);
    }
    //load font for expression text
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "ERROR" << endl;
        cin.get();
        exit(-1);

    }
    //set text pos color font size and style
    text.setPosition(400, 0);
    text.setFillColor(Color::Red);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setStyle(Text::Bold);

    text2.setFont(font);
    text2.setCharacterSize(16);
    text2.setFillColor(Color::White);
    text2.setStyle(Text::Italic);




    //get coordinates
    Input.getCoordin();
    //prints string to sidebar
    userExp = Input.get_exp();
    Sidebar.set_infix(userExp);

}

void user::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();

    }
}

void user::processEvents()
{
    Event event;
    float mouseX, mouseY;
    while (window.pollEvent(event))
    {
        //when space is entered only allow expression to be inputted
        if (event.key.code == Keyboard::Space || expFlag == true)
        {
            //creates new box on screen for input
            if (event.key.code == Keyboard::Space)
            {
                command = NEW;
                expFlag = true;

                text2.setPosition(0, 0);
                text2.setString("[Enter]: Enter Typed Expression");
                window.draw(text2);




            }
            //when enter is pressed send that string to parse which uses shunting yard
            //add that str to another string that outputs to sidebar
            else if (event.key.code == Keyboard::Enter)
            {
                Input.parse(userInput);
                history += (userInput);
                history += '\n';
                Sidebar.set_infix(history);
                Input.getCoordin();
                command = DELETE;
                expFlag = false;
                userFlag = false;
                userInput = "";
            }
            //backspace delets from string like typing
            else if (event.key.code == Keyboard::Backspace)
            {

                userInput.pop_back();
                text.setString(userInput);
                userFlag = true;
            }

            else
            {

                if (event.type == Event::TextEntered)
                {
                    //takes user input and sets it to screen and makes it a string
                    userInput += event.text.unicode;
                    text.setString(userInput);
                    userFlag = true;

                }

            }
        }


        else
        {


            switch (event.type)
            {


            case Event::Closed:
                window.close();
                break;

            case Event::KeyPressed:
                switch (event.key.code)
                {
                    //close window
                case::Keyboard::Q:
                    window.close();
                    break;
                    //go right
                case::Keyboard::Right:
                    command = GORIGHT;
                    break;
                    //go left
                case::Keyboard::Left:
                    command = GOLEFT;
                    break;
                    //go up
                case::Keyboard::Up:
                    command = GOUP;
                    break;
                    //go down
                case::Keyboard::Down:
                    command = GODOWN;
                    break;
                    //reset postion
                case::Keyboard::R:
                    command = RESET;
                    break;
                    ///zoom in
                case::Keyboard::I:
                    command = IN;
                    break;
                    //zoom out
                case::Keyboard::O:
                    command = OUT;
                    break;
                case::Keyboard::G:
                    command = IDK;
                    break;
                case::Keyboard::F:
                    command = IDK2;
                    break;


                }
            break; case Event::MouseEntered:
                mouseIn = true;
                break;

            case Event::MouseLeft:
                mouseIn = false;
                break;
                //while mouse is over graph make it and hand on sidebar make it a text
            case Event::MouseMoved:
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
                if (mouseX >= GRAPH_PANEl && mouseX <= SCREEN_WIDTH)
                {
                    if (cursor.loadFromSystem(sf::Cursor::Text))
                        window.setMouseCursor(cursor);
                }
                else
                {
                    if (cursor.loadFromSystem(sf::Cursor::Hand))
                        window.setMouseCursor(cursor);
                }
                break;
            case Event::MouseButtonReleased:
                if (event.mouseButton.button == Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }


            }

        }

    }


}


void user::update()
{

    //sends what to do from proccess events
    Input.step(command);
    command = 0;
}


void user::render()
{
    if (userFlag == true)
    {
        window.clear();
        draw();
        window.draw(text);
        window.draw(text2);
        window.display();
    }
    if (userFlag == false)
    {
        window.clear();
        window.draw(text);
        window.draw(text2);
        draw();
        window.display();
    }
}

void user::draw()
{
    //draws sidebar and equation

    if (userFlag == true)
    {
        Input.Draw(window);
        Sidebar.draw(window);
    }

    else
    {
        Input.Draw(window);
        Sidebar.draw(window);
        Menu.draw(window);
    }


}