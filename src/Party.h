#ifndef GAME_PARTY_H
#define GAME_PARTY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <map>
#include <memory>

#include "Position.h"

class Party{

public:
    Party();
    ~Party();

    void run();

private:

    void loadTextures();
    sf::Texture& getTexture(const std::string&);

    void processEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time);
    void render();

    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;

    float PlayerSpeed = 25.f;

private:

    std::map<std::string, sf::Texture*> textures;

    //std::vector<sf::Sprite> // sprite.getGlobalBounds() renvoie un sf::FloatRect (rect.top rect.left rect.width rect.length) sera très utile pour les colisions !

    sf::RenderWindow mWindow;

    sf::Texture mTexture;
    sf::Sprite mPlayer;

    Position<float> posEntity;
};

#endif