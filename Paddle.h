//
// Created by Nitin Nagarkar on 3/21/24.
//

#ifndef SFMLSD_PADDLE_H
#define SFMLSD_PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle {
public:
    // Constructor for initializing paddle position and size
    Paddle(float x, float y, float width, float height) :
            position(x, y), size(width, height), velocity(0.0f, 0.0f) {}

    // Function to update paddle position and velocity based on user input
    void update(sf::RenderWindow& window) {
        const float movementSpeed = 200.0f;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        velocity.y = -movementSpeed;
                        break;
                    case sf::Keyboard::Down:
                        velocity.y = movementSpeed;
                        break;
                        // Add cases for left and right movement if needed
                    default:
                        break;
                }
            } else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                    case sf::Keyboard::Down:
                        velocity.y = 0.0f;
                        break;
                        // Add cases for left and right movement if needed
                    default:
                        break;
                }
            }
        }

        // Update position based on velocity (clamped to prevent going out of bounds)
        position += velocity;
//        position.y = std::clamp(position.y, 0.0f, window.getSize().y - size.y);
    }

    // Getter functions for position, velocity, and size
    const sf::Vector2f& getPosition() const { return position; }
    const sf::Vector2f& getVelocity() const { return velocity; }
    const sf::Vector2f& getSize() const { return size; }

private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f velocity;
};

#endif //SFMLSD_PADDLE_H
