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

    void loadSprites(std::string name);
    sf::Sprite getSprite(const std::string&); // On donne la categorie du sprite, et le nom de la texture

    void processEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time);
    void render();

    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;

    float PlayerSpeed = 50.f;

private:

    std::map<std::string, sf::Texture*> textures;
    std::map<std::string, sf::Sprite> sprites;

    //std::vector<sf::Sprite> // sprite.getGlobalBounds() renvoie un sf::FloatRect (rect.top rect.left rect.width rect.length) sera très utile pour les colisions !

    sf::RenderWindow mWindow;

    sf::Sprite sPlayer;
    sf::Sprite sRock;

    Position<float> posEntity;
};

#endif
