#ifndef GAME_PARTY_H
#define GAME_PARTY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>

#include "Position.h"
#include "Entity.h"
#include "Donjon.h"
    // Utilisés pour récupérer les infos de leurs placements
#include "Room.h"
#include "Door.h"
#include "Chest.h"

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

    void setDoorOpenSprites(Room);
    void setDoorCloseSprites(Room);
    void setFrameSprite(Room);
    void setRockSprites(Room);
    //void setMonsterSprites(Room);
    void setChestOpenSprites(Room);

    void setSpritesForCurrentRoom(unsigned, unsigned);

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

    Position<unsigned> posDonjon;
    Entity Aspen;
    Donjon donjon;

    std::map<std::string, sf::Texture*> textures;
    std::map<std::string, sf::Sprite> sprites;

    sf::RenderWindow mWindow;

        // Différents sprites pouvant être sur la map
    sf::Sprite sPlayer;
    sf::Sprite sRoom;
    std::vector<sf::Sprite> sMonsters;
    std::vector<sf::Sprite> sRocks;
    std::vector<sf::Sprite> sFrames;
    std::vector<sf::Sprite> sDoors;
    std::vector<sf::Sprite> sChest;

};

#endif
