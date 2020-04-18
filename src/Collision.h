#ifndef GAME_COLLISION_H
#define GAME_COLLISION_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Collision{

public:
    Collision(sf::RectangleShape &body);
    ~Collision();

    void Move(float dx, float dy);

    bool checkCollision(Collision &other, float push);

    sf::Vector2f getPosition();
    sf::Vector2f getHalfSize();

private:
    sf::RectangleShape &body;
};

#endif