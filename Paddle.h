//
// Created by Nitin Nagarkar on 3/21/24.
//

#ifndef PADDLE_H
#define PADDLE_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

void movePaddle(sf::Event& event,sf::RectangleShape& paddle, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey);
void checkCollision(sf::CircleShape& ball, sf::RectangleShape& paddle1, sf::RectangleShape& paddle2, sf::Sound& hit, sf::Vector2f& ballVelocity, std::mt19937& gen, float& angle);


#endif //PADDLE_H
