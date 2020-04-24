#ifndef GAME_PARTY_H
#define GAME_PARTY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <cmath>

#include "AnimatedSprite.h"

#include "Position.h"
#include "Entity.h"
#include "Donjon.h"
#include "Collider.h"
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

    void loadAnimation();

    void setWall();
    void setHole(Room&);
    void setDoorOpenRectangleShape(Room&);
    void setDoorCloseRectangleShape(Room&);
    void setRockRectangleShape(Room&);
    //void setMonsterRectangleShape(Room);
    void setChestRectangleShape(Room&);
    void setTrapRectangleShape(Room&);
    void setRectangleShapeForCurrentRoom();

    void setInventoryItem(); // bag et stuff
    void setChestItem(Room&);

    void setScrollingMenu();
    void updateScrollingMenu();
	void updateMoveObject();
    void updateInventory();
    void drawPlayerInventory();
	
	void reloadRoom();
    void loadNextStage();

    void entityCollision();

    void processEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time);
    void render();

    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;
	bool noKeyWasPressed = true;

    float PlayerSpeed = 250.f;

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
    std::vector<sf::RectangleShape> sTrap;
    std::vector<sf::RectangleShape> Walls;
    std::vector<sf::RectangleShape> Holes;
    std::vector<sf::RectangleShape> sMonsters;
    std::vector<sf::RectangleShape> sRocks;
    std::vector<sf::Sprite> sFrames;
    std::vector<sf::RectangleShape> sDoors;
    std::vector<sf::RectangleShape> sChest;
    //std::vector<sf::RectangleShape> sProjectiles;
	
	Collider trapCollider;
	Collider wallsCollider;
	Collider holesCollider;
	Collider rocksCollider;
	Collider doorsCollider;
	// Collider monstersCollider;
	Collider chestsCollider;
	// Collider projectilesCollider;
	
	Archetype arch;

	    //  Aspen animation

	Animation *currentAnimation;
	AnimatedSprite aspenAnimated;

	Animation walkingAspenUp;
	Animation walkingAspenRight;
	Animation walkingAspenDown;
	Animation walkingAspenLeft;

	    // Inventory / Chest
	bool inventoryOpen = false; // si l'inventaire est ouvert bloque les mouvements du player et ne permet que les mouvements dans l'inventaire
	sf::RectangleShape playerInventory;
	sf::RectangleShape chestInventory;

	std::map<unsigned, sf::RectangleShape> bagItem;
	std::map<unsigned, sf::RectangleShape> stuffItem;
	std::map<unsigned, sf::RectangleShape> chestItem; // Si pas d'item, le rectangleShape est blanc, unsigned -> place dans l'inventaire
	std::map<unsigned, sf::Text> objectsNumber;
	sf::Font objectsFont;
	
	sf::RectangleShape sInventoryCursor;
    unsigned inventoryValue; // 1: stuff, 2: bag, 3: chest
    unsigned inventoryIndex; // valeur de l'index selectionné
        // scrolling  menu
    bool scrollingMenuOpen = false;
    sf::Font scroll;
    
    std::vector<sf::Text> textScrolling;
    std::vector<sf::RectangleShape> rectangleShapeScrolling;
    unsigned scrollingValue;
    unsigned scrollingIndex;
	
	sf::RectangleShape scrollingMenuCursor;
	
	bool moveObjectOpen = false;
	sf::RectangleShape moveCursor;
	unsigned moveObjectIndex;
};

#endif
