#ifndef GAME_PARTY_H
#define GAME_PARTY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <utility>

#include "Position.h"
#include "Entity.h"
#include "Donjon.h"
#include "Collision.h"
#include "Archetype.h"
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
    sf::Texture* getTexture(const std::string&);

    void loadSprites(std::string name);
    sf::Sprite getSprite(const std::string&); // On donne la categorie du sprite, et le nom de la texture

    void setFrameSprite(Room&);
    void setSpritesForCurrentRoom();

    void loadRectangleShape(std::string name);
    sf::RectangleShape getRectangleShape(const std::string&);

    void setWall();
    void setDoorOpenRectangleShape(Room&);
    void setDoorCloseRectangleShape(Room&);
    void setRockRectangleShape(Room&);
    //void setMonsterRectangleShape(Room);
    void setChestRectangleShape(Room&);
    void setRectangleShapeForCurrentRoom();
	
	void reloadRoom();

    void entityCollision();

    void processEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time);
    void render();

    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;

    float PlayerSpeed = 150.f;

private:

    Position<int> posDonjon;
    Position<float> posAspen;
    Entity Aspen;
    Donjon donjon;

        // Maps des différents élément à afficher
    std::map<std::string, sf::Texture*> textures;
    std::map<std::string, sf::Sprite> sprites;
    std::map<std::string, sf::RectangleShape*> rectangleShapes;

    sf::RenderWindow mWindow;

        // Différents sprites/rectangleShape pouvant être sur la map
    sf::RectangleShape sPlayer;
    sf::Sprite sRoom;
    std::vector<sf::RectangleShape> Walls;
    std::vector<sf::RectangleShape> sMonsters;
    std::vector<sf::RectangleShape> sRocks;
    std::vector<sf::Sprite> sFrames;
    std::vector<sf::RectangleShape> sDoors;
    std::vector<sf::RectangleShape> sChest;

    std::vector<Collision> collisions;
	
	Archetype arch;
};

#endif
