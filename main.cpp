// All the libraries used
/* Name: Nitin Nagarkar - Odyssey
 * Project: Pong Game (2D)
 * Start page, then game begins with a toss
 */
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <random>

using namespace sf;
using namespace std;

// Main block
int main()
{

    enum GameState{Instructions,toss,ready,play,winner,end};
    GameState state = Instructions;


    int dir = 0; // to decide the direction of the ball
    sf::RenderWindow window(sf::VideoMode(1000, 480), "SFML Tennis Game"); // creating a window of certain size
    sf::Texture t1;
//    sf::View view(sf::FloatRect(0, 0, 750, 480)); // Initial viewport setup
//    window.setView(view);
//     setting a variable for the background
    t1.loadFromFile("images/ping_pong.jpeg");
    sf::Sprite background(t1); // loading the background
    window.setFramerateLimit(30); // sprite frame rate


    sf::Text text2;
    sf::Text text3;
    sf::Text text4;
    sf::Text text5;
    sf::Text text6;
    sf::Text text7;
    sf::Text text8;
    sf::Text text9;
    sf::Text text10;



    background.setScale(1.80,1.90); // changing the scale of the background


    // Set up the paddles
    sf::RectangleShape paddle1(sf::Vector2f(20, 100));


    paddle1.setFillColor(Color::Black);
    paddle1.setOutlineColor(Color::Magenta);
    paddle1.setOutlineThickness(3);

    sf::RectangleShape paddle2(sf::Vector2f(20, 100));


    paddle2.setFillColor(Color::Black);
    paddle2.setOutlineColor(Color::Magenta);
    paddle2.setOutlineThickness(3);

    // Set up the ball
    sf::CircleShape ball(15);
    //ball.setPosition(375, 240);

    ball.setFillColor(Color::Green);
    ball.setOutlineColor(Color::Black);
    ball.setOutlineThickness(3);


    // Set up ball movement
    Vector2f ballVelocity(5, 5);

    sf::RectangleShape button(sf::Vector2f(200, 30));
    button.setFillColor(Color::Black);
    button.setOutlineColor(Color:: Red);
    button.setOutlineThickness(5);

    sf::RectangleShape button2(sf::Vector2f(200, 30));
    button2.setFillColor(Color::Black);
    button2.setOutlineColor(Color:: Red);
    button2.setOutlineThickness(5);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> angleDist(45.0f, 135.0f); // Adjust angle range as needed
    float angle = angleDist(gen);

    ballVelocity.x = 10;
    ballVelocity.y = 20 * sin(angle * M_PI / 180.0f);

    int player1Score = 0;
    int player2Score = 0;


    // Load font for text display
    sf::Font font;
    sf::Font font2;

    const float movementSpeed = 200.0f;

    window.draw(background);
    if (!font.loadFromFile("font/font.ttf"))
    {
        // Handle font loading error
        return -1;
    }
    if (!font2.loadFromFile("font/font.ttf"))
    {
        // Handle font loading error
        return -1;
    }
    text9.setFont(font);
    text9.setCharacterSize(20);
    text9.setFillColor(sf::Color:: Yellow);
    text9.setStyle(sf::Text::Bold);
    text9.setPosition(300,400);

    text10.setFont(font);
    text10.setCharacterSize(20);
    text10.setFillColor(sf::Color:: Yellow);
    text10.setStyle(sf::Text::Bold);
    text10.setPosition(300,400);

    int score1 = 0;
    int score2 = 0;

    string YourScore1;
    string YourScore2;

    while (window.isOpen())
    {
//        sf::Event event5;
//        while (window.pollEvent(event5)) {
//            if (event5.type == sf::Event::Closed)
//                window.close();
//            else if (event5.type == sf::Event::Resized) {
//                // Adjust the viewport to keep the game world visible
//                sf::FloatRect visibleArea(0, 0, event5.size.width, event5.size.height);
//                window.setView(sf::View(visibleArea));
//            }
//        }

        if (state == Instructions) // when state is Instructions
        {
            window.draw(background);

            text2.setFont(font);
            text2.setCharacterSize(25); // setting the character size in pixels
            text2.setFillColor(sf::Color::Yellow); // setting the color of the font
            text2.setStyle(sf::Text::Bold); // text style
            text2.setPosition(90,130); // position of the text
            text2.setString("      WELCOME!!\n"
                            "This is Tennis Pong!\n"
                            "Face-off with your Opponent!\n "
                            "First person to reach 10 points\n "
                            " WINS !! "
                            "Good luck!!"); // the contents of the string that needs to be displayed

            text9.setPosition(300,400);
            text9.setString("Choose Opponent");
            button.setPosition(300, 400);

            window.draw(text2);
            window.draw(button);
            window.draw(text9);



            Event p; // a new event type variable
            while (window.pollEvent(p)) // window event
            {
                if (p.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (p.type == sf::Event::MouseMoved)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (text9.getGlobalBounds().contains(mousePos)) {
                        // Mouse is hovering over the text
                        text9.setFillColor(sf::Color::Red);
                        window.draw(text9);
                    }

                }

                if (p.type == sf::Event::MouseButtonPressed)
                {
                    if (p.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        if (text9.getGlobalBounds().contains(mousePos))
                        {
                            // Mouse left button is pressed while hovering over the text
                            // Perform animation here (e.g., scale the text)
                            text9.setScale(1.2f, 1.2f);
                            state = toss;


                        }

                    }
                }

                if (p.type == sf::Event::MouseButtonReleased)
                {
                    if (p.mouseButton.button == sf::Mouse::Left)
                    {
                        // Mouse left button is released
                        // Reset the text scale to its original size
                        text9.setScale(1.0f, 1.0f);

                    }

                }

            }
//            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//            {
//                state = toss;
//            }
        }

        if (state == toss)
        {
            window.draw(background);

            text2.setFont(font);
            text2.setCharacterSize(40); // setting the character size in pixels
            text2.setFillColor(sf::Color::Black); // setting the color of the font
            text2.setStyle(sf::Text::Bold); // text style
            text2.setPosition(90,200); // position of the text
            text2.setString(" HEADS "); // the contents of the string that needs to be displayed
            text4.setFont(font);
            text4.setCharacterSize(40); // setting the character size in pixels
            text4.setFillColor(sf::Color::Black); // setting the color of the font
            text4.setStyle(sf::Text::Bold); // text style
            text4.setPosition(460,200); // position of the text
            text4.setString(" TAILS "); // the contents of the string that needs to be displayed

            window.draw(text2);
            window.draw(text4);

            sf::Event event;
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (event.type == sf::Event::MouseMoved)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (text2.getGlobalBounds().contains(mousePos)) {
                        // Mouse is hovering over the text
                        text2.setFillColor(sf::Color::Red);
                        window.draw(text2);
                    }
                    if (text4.getGlobalBounds().contains(mousePos)) {
                        // Mouse is hovering over the text
                        text4.setFillColor(sf::Color::Red);
                        window.draw(text4);
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        if (text2.getGlobalBounds().contains(mousePos))
                        {
                            // Mouse left button is pressed while hovering over the text
                            // Perform animation here (e.g., scale the text)
                            text2.setScale(1.2f, 1.2f);
                            state = ready;
                            ball.setPosition(70, 240);

                        }
                        else if (text4.getGlobalBounds().contains(mousePos))
                        {
                            // Mouse left button is pressed while hovering over the text
                            // Perform animation here (e.g., scale the text)
                            text4.setScale(1.2f, 1.2f);
                            state = ready;
                            ball.setPosition(650, 240);
                        }
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        // Mouse left button is released
                        // Reset the text scale to its original size
                        text2.setScale(1.0f, 1.0f);
                        text4.setScale(1.0f, 1.0f);
                    }

                }
            }

        }

        if (state == ready)
        {

            paddle1.setPosition(50, 200);
            paddle2.setPosition(680, 200);
            YourScore1 = to_string(score1);
            YourScore2 = to_string(score2);

            text5.setFont(font); // select the font
            text5.setCharacterSize(24); // setting the character size in pixels
            text5.setFillColor(sf::Color::Red); // setting the color of the font
            text5.setStyle(sf::Text::Bold); // text style
            text5.setPosition(800,400);
            text5.setString("PLayer 1: ");

            text6.setFont(font); // select the font
            text6.setCharacterSize(24); // setting the character size in pixels
            text6.setFillColor(sf::Color::Red); // setting the color of the font
            text6.setStyle(sf::Text::Bold); // text style
            text6.setPosition(800,440);
            text6.setString("Player 2: ");

            text7.setFont(font); // select the font
            text7.setCharacterSize(24); // setting the character size in pixels
            text7.setFillColor(sf::Color::Red); // setting the color of the font
            text7.setStyle(sf::Text::Bold); // text style
            text7.setPosition(960,400);
            text7.setString(YourScore1);

            text8.setFont(font); // select the font
            text8.setCharacterSize(24); // setting the character size in pixels
            text8.setFillColor(sf::Color::Red); // setting the color of the font
            text8.setStyle(sf::Text::Bold); // text style
            text8.setPosition(960,440);
            text8.setString(YourScore2);




            window.draw(background);
            window.draw(paddle1);
            window.draw(paddle2);
            window.draw(ball);
            window.draw(text5);
            window.draw(text6);
            window.draw(text7);
            window.draw(text8);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B)
                {
                    state = play;
                }
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

        }


        if (state == play)
        {
            // Logic for ball moving left right ( x bounds are the paddle's x pos)
//        if (ball.getPosition().x <= 0)
//        {
//            dir = 1;
//        }
//        else if (ball.getPosition().x + ball.getRadius() >= window.getSize().x)
//        {
//            dir = 0;
//        }
//
//        if (dir == 0)
//        {
//            ball.move(-10.f,0);
//
//        }
//        else
//        {
//            ball.move(10.f,0);
//
//        }
            ball.move(ballVelocity);

            // Ball collision with paddles (and random bounce)
            /*const float collisionThreshold = 1.0f; // Adjust the threshold as needed

            if (std::abs(ball.getPosition().x - paddle1.getPosition().x) < collisionThreshold)
            {
                // Handle collision
                ballVelocity.x = -ballVelocity.x;
                angleDist = std::uniform_real_distribution<float>(-45.0f, 45.0f);
                angle = angleDist(gen);
                ballVelocity.y = 5 * sin(angle * M_PI / 180.0f);
                ball.move(ballVelocity);
                ball.setFillColor(Color::Yellow);
                ball.setOutlineColor(Color::Black);
            }*/
            if (ball.getPosition().x + ball.getRadius() >= paddle1.getPosition().x &&
                ball.getPosition().x - ball.getRadius() <= paddle1.getPosition().x &&
                ball.getPosition().y + ball.getRadius() >= paddle1.getPosition().y &&
                ball.getPosition().y - ball.getRadius() <= paddle1.getPosition().y + paddle1.getSize().y)
            {
                // Ball is approaching from the right, reverse x and set a random y velocity
                ballVelocity.x = -ballVelocity.x; // Ensure positive x velocity
                angleDist = std::uniform_real_distribution<float>(-45.0f, 45.0f);
                angle = angleDist(gen);
                ballVelocity.y = 20 * sin(angle * M_PI / 180.0f);
            }
            else if (ball.getPosition().x - ball.getRadius() <= paddle2.getPosition().x  &&
                     ball.getPosition().x + ball.getRadius() >= paddle2.getPosition().x &&
                     ball.getPosition().y + ball.getRadius() >= paddle2.getPosition().y &&
                     ball.getPosition().y - ball.getRadius() <= paddle2.getPosition().y + paddle2.getSize().y)
            {
                // Ball is approaching from the left, reverse x and set a random y velocity
                ballVelocity.x = -ballVelocity.x; // Ensure negative x velocity
                angleDist = std::uniform_real_distribution<float>(-45.0f, 45.0f);
                angle = angleDist(gen);
                ballVelocity.y = 20* sin(angle * M_PI / 180.0f);
            }

            if (ball.getPosition().y < 0 || ball.getPosition().y + ball.getRadius() * 2 > 480)
            {
                ballVelocity.y = -ballVelocity.y;
            }
            if (ball.getPosition().x < 0 || ball.getPosition().x + ball.getRadius() * 2 > 750)
            {
                ballVelocity.x = -ballVelocity.x;

            }
            if(ball.getPosition().x+ ball.getRadius() * 2 > 750)
            {
                score2++;
                YourScore2 = to_string(score2);
            }
            if(ball.getPosition().x < 0)
            {
                score1++;
                YourScore1 = to_string(score1);
            }

            if (score1 > 10 || score2 > 10)
            {
                state = winner;
            }


            // Process events
            sf::Event event;
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                //PADDLE 1 MOVING

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
                {
                    paddle2.move(0,-20);
                }
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
                {
                    paddle2.move(0,20);
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
                {
                    paddle2.move(-20,0);
                }
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
                {
                    paddle2.move(20,0);

                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        // Get the position where the mouse was clicked
                        sf::Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);
                        // Move the sprite to the clicked position
                        if (event.mouseButton.x > 375)
                        {
                            paddle2.setPosition(clickPosition);
                        }

                        else
                        {
                            paddle1.setPosition(clickPosition);
                        }

                    }
                }

                //paddle1.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
                // PADDLE 2 Moving
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
                {
                    paddle1.move(0,-20);
                }
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
                {
                    paddle1.move(0,20);
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
                {
                    paddle1.move(-20,0);
                }
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
                {
                    paddle1.move(20,0);
                }

            }
            text5.setFont(font); // select the font
            text5.setCharacterSize(24); // setting the character size in pixels
            text5.setFillColor(sf::Color::Red); // setting the color of the font
            text5.setStyle(sf::Text::Bold); // text style
            text5.setPosition(800,400);
            text5.setString("PLayer 1: ");

            text6.setFont(font); // select the font
            text6.setCharacterSize(24); // setting the character size in pixels
            text6.setFillColor(sf::Color::Red); // setting the color of the font
            text6.setStyle(sf::Text::Bold); // text style
            text6.setPosition(800,440);
            text6.setString("Player 2: ");

            text7.setFont(font); // select the font
            text7.setCharacterSize(24); // setting the character size in pixels
            text7.setFillColor(sf::Color::Red); // setting the color of the font
            text7.setStyle(sf::Text::Bold); // text style
            text7.setPosition(960,400);
            text7.setString(YourScore1);

            text8.setFont(font); // select the font
            text8.setCharacterSize(24); // setting the character size in pixels
            text8.setFillColor(sf::Color::Red); // setting the color of the font
            text8.setStyle(sf::Text::Bold); // text style
            text8.setPosition(960,440);
            text8.setString(YourScore2);




            // Clear the window
            window.clear();

            // Draw paddles and ball
            window.draw(background);
            window.draw(paddle1);
            window.draw(paddle2);
            window.draw(ball);
            window.draw(text5);
            window.draw(text6);
            window.draw(text7);
            window.draw(text8);

        }

        if (state == winner)
        {
            text3.setFont(font);
            text3.setCharacterSize(35); // setting the character size in pixels
            text3.setFillColor(sf::Color::Yellow); // setting the color of the font
            text3.setStyle(sf::Text::Bold); // text style
            text3.setPosition(50,200); // position of the text
            if (score1 > score2)
            {
                text3.setString("       Player 1 wins!\n "
                                "You move to the second round\n"); // the contents of the string that needs to be displayed
                text9.setPosition(100,400);
                text9.setString("Next Round");
                button.setPosition(100, 400);
                text10.setPosition(500,400);
                text10.setString("End Game");
                button2.setPosition(500,400);

            }
            else
            {
                text3.setString("       Player 2 wins!\n "
                                "You move to the second round\n"); // the contents of the string that needs to be displayed
                text9.setPosition(100,400);
                text9.setString("Next Round");
                button.setPosition(100, 400);
                text10.setPosition(500,400);
                text10.setString("End Game");
                button2.setPosition(500,400);
            }
            sf::Event event;
            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N)
                {
                    state = toss;
                    score1 = 0;
                    score2 = 0;
                }
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
                {
                    state = end;
                }


            }


            window.draw(background);
            window.draw(text3);
            window.draw(button);
            window.draw(button2);
            window.draw(text9);
            window.draw(text10);

        }

        if (state == end)
        {
            window.close();
        }



        // Display the contents of the window
        window.display();
    }

    return 0;

}

