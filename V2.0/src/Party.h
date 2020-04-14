#ifndef GAME_PARTY_H
#define GAME_PARTY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>

#include "Position.h"

class Party{

public:
    Party();
    void run();

private:
    void processEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time);
    void render();

    void loadTexture(sf::Texture &, std::string)
    void affectPositionTextureToSprite(sf::Sprite &, sf::Texture, Position);

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

    float PlayerSpeed = 25.f;

private:
    sf::RenderWindow mWindow;

    sf::Texture mTexture;
    sf::Sprite mPlayer;

    Position posEntity;
};

#endif