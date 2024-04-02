//
// Created by Nitin Nagarkar on 3/21/24.
//

#ifndef SFMLSD_BALL_H
#define SFMLSD_BALL_H
#include <SFML/Graphics.hpp>

class Ball {
public:
    // Constructor for initializing ball position, size, and velocity
    Ball(float x, float y, float radius, float velocityX, float velocityY) :
            position(x, y), radius(radius), velocity(velocityX, velocityY) {}

    // Function to update ball position, handling collisions with walls (placeholders)
    void update(const sf::RenderWindow& window) {
        // Update position based on velocity
        position += velocity;

        // Placeholder for wall collisions (adjust boundaries as needed)
        if (position.y < 0.0f || position.y + radius * 2.0f > window.getSize().y) {
            velocity.y = -velocity.y;
        }

        if (position.x < 0.0f || position.x + radius * 2.0f > window.getSize().x) {
            velocity.x = -velocity.x;
        }
    }

    // Getter functions for position, radius, and velocity
    const sf::Vector2f& getPosition() const { return position; }
    const float getRadius() const { return radius; }
    const sf::Vector2f& getVelocity() const { return velocity; }

private:
    sf::Vector2f position;
    float radius;
    sf::Vector2f velocity;
};
#endif //SFMLSD_BALL_H
