#ifndef GAME_PARTY_H
#define GAME_PARTY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <utility>
#include <cmath>
#include <cstdlib>

#include "AnimatedSprite.h"

#include "Position.h"
#include "Entity.h"
#include "Donjon.h"
#include "Projectile.h"
#include "Collider.h"
#include "Archetype.h"
    // Utilisés pour récupérer les infos de leurs placements
#include "Room.h"
#include "Door.h"
#include "Chest.h"
#include "aStar.h"

class Party{

public:
    Party();
    ~Party();

    void run();

private:

    std::string returnCsvItem(std::istringstream &);
    /**
     * @brief loads textures according
    */
    void loadTextures();
    
    /** 
     * @brief search for a texture given in parameter
     * @param[in] name : a string the name of the textures to search
     * @return texture if found or not
     */
    sf::Texture* getTexture(const std::string&);

    /**
     * @brief load sprites
     */
    void loadSprites(std::string name);
    
    /** 
     * @brief search for a sprite given in parameter
     * @param[in] name : a string the name of the sprite to search
     * @return sprite if found or not
     */
    sf::Sprite getSprite(const std::string&); // On donne la categorie du sprite, et le nom de la texture


    void setFrameSprite(Room&);
    void setSpritesForCurrentRoom();

    void loadRectangleShape(std::string name);
    sf::RectangleShape getRectangleShape(const std::string&);

    /**
     * @brief the animations of the player according to whether the sprite is walking up, down, left, right
    */
    void loadAnimation();

    void setWall();
    void setHole(Room&);
    void setDoorOpenRectangleShape(Room&);
    void setDoorCloseRectangleShape(Room&);
    void setRockChoice(Room&);
    void setRockRectangleShape(Room&);

    void setMonsterRectangleShape(Room&);
    void setLootOnTheFloor(Entity&);
    void drawLootOnTheFloor();

    void setLifeRectangleShape();
    void updateLife();

    void setAStar(Room&);
    void updateGrippeEspagnole(Entity&, sf::Time, unsigned);
    void updatePesteNoire(Entity&, sf::Time, unsigned);
    void updateTenia(Entity&, sf::Time);
    void updateListeria(Entity&, sf::Time);
    void updateBlob(Entity&, sf::Time);
    void updateCymothoaExigua(Entity&, sf::Time, unsigned);
    void updateH1N1(Entity&, sf::Time, unsigned);
    void updateVIH(Entity&, sf::Time);
    void updateCOVID19(Entity&, sf::Time, unsigned);

    void updateMonsters(sf::Time);
    void setChestRectangleShape(Room&);
    void setTrapRectangleShape(Room&);
    sf::Texture* selectProjectileTexture(const Entity&, unsigned);
    void setProjectileRectangleShape(const Entity&, unsigned); // l'entity afin de récupérer sa position, unsigned 0 -> 4 pour son orientation
    void updateProjectile();
    void drawProjectile();
    void setRectangleShapeForCurrentRoom();

    void setInventoryStats(); // pour afficher les stats du joueur
    sf::Color setItemLvl(unsigned);
    void setInventoryItem(); // bag et stuff
    void setChestItem(Room&);

    void setScrollingMenu();
    void updateScrollingMenu();
	void updateMoveObject();
    void updateInventory();
    void drawChestInventory();
    void drawPlayerInventory();
    
    void updateException();
    void drawException();
	
	void reloadRoom();
	
	/**
	 * @brief loads the next stage, sets apsen to the new position, loads next stage, calls realoadRoom
    */
    void loadNextStage();

    /**
     * @brief check for collisions
    */
    void entityCollision();

    void removeLife(Projectile*, Entity*);
    void projectileCollision();

    /**
     * @brief an event loop, with input from player(close window, keyPressed and released)
    */
    void processEvents();
    
    /**
     * @brief gets the input from the player on keyboard only
     * @param[in] key : sfml keyboard input parameter
     * @param[in] isPressed : is key pressed
    */
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    void updateForShooting(sf::Time);

    /**
     * @brief calls the correct functions when player going up,down...
    */
    void update(sf::Time);
    
    /**
     * @brief render function
    */
    void render();

    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;
    bool mIsShootingUp = false;
    bool mIsShootingLeft = false;
    bool mIsShootingRight = false;
    bool mIsShootingDown = false;
	bool noKeyWasPressed = true;

    float PlayerSpeed;

private:

    Position<int> posDonjon;
    Position<float> posAspen;
    Entity Aspen; // a passer en donné resultat par le constructeur à terme
    Donjon donjon;
    Archetype arch; // Pour récupérer toutes les positions pour placer les images

        // Maps des différents élément à afficher
    std::map<std::string, sf::Texture*> textures;
    std::map<std::string, sf::Sprite> sprites;
    std::map<std::string, sf::RectangleShape*> rectangleShapes;

    sf::RenderWindow mWindow;

    // Pour le VIH
    unsigned stat[6] = {1, 2, 2, 3, 3, 3};
    std::vector<std::pair<unsigned, sf::Vector2f>> vectorVIH; // (etat, Vector de direction)

    // Pour les projectiles
    sf::Time elapsedTime;
    sf::Time aspenAttackSpeed;

    std::vector<Entity*> flyMonst;
    std::vector<Entity*> walkMonst;

    // Différents sprites/rectangleShape pouvant être sur la map
    sf::Sprite sRoom;
    std::vector<sf::RectangleShape> Walls;
    std::vector<sf::RectangleShape> Holes;
    std::vector<sf::RectangleShape> sFlyingMonsters;
    std::vector<sf::RectangleShape> sWalkingMonsters;
    std::vector<unsigned> sLoot; // Id des objets
    std::vector<sf::Sprite> Loots; // Image des objets
    std::vector<sf::RectangleShape> hitBoxLoots; // retangle shape pour les collision avec le joueur
    std::vector<sf::Vector2f> destinationMonster;
    std::vector<bool> inActionMonster;
    std::vector<sf::Time> actionTimeMonster;
    std::vector<sf::Time> pauseTimeMonster;
    std::vector<sf::RectangleShape> sRocks;
	std::vector<sf::RectangleShape> sNoRocks;
	std::vector<unsigned> rocksChoice;
    std::vector<sf::Sprite> sFrames;
    std::vector<sf::RectangleShape> sDoors;
    std::vector<sf::RectangleShape> sChest;
    std::vector<sf::RectangleShape> sTrap;
    std::map<Projectile*, sf::RectangleShape> sProjectiles; // pour update, on parcour le map, on appel sProjectile.first->update() et on modifie sProjectile.second en fonction de la nouvelle position

    Collider wallsCollider;
    Collider holesCollider;
    Collider flyingMonstersCollider;
    Collider walkingMonstersCollider;
    Collider lootCollider;
    Collider rocksCollider;
    Collider doorsCollider;
    Collider chestsCollider;
	Collider trapCollider;

	    //  Aspen animation

	Animation *currentAnimation;
	AnimatedSprite aspenAnimated;

	Animation walkingAspenUp;
	Animation walkingAspenRight;
	Animation walkingAspenDown;
	Animation walkingAspenLeft;

	    // Aspen Life
	sf::RectangleShape sMaxLife;
	sf::RectangleShape sLife;

	    // Inventory / Chest
	bool inventoryOpen = false; // si l'inventaire est ouvert bloque les mouvements du player et ne permet que les mouvements dans l'inventaire
	sf::RectangleShape playerInventory;
    sf::RectangleShape viewAspen; // image du joueur dans l'inventaire

	bool chestOpen = false;
	sf::RectangleShape chestInventory;

	std::map<unsigned, sf::Sprite> bagItem;
	std::map<unsigned, sf::Sprite> stuffItem;
	std::map<unsigned, sf::Sprite> chestItem; // Si pas d'item, le rectangleShape est blanc, unsigned -> place dans l'inventaire
	std::map<unsigned, sf::Text> objectsNumber;
	std::map<unsigned, sf::Text> chestObjectNumber;
	sf::Font objectsFont;
	
	// stats for player's inventory
	sf::Font statsFont;
	std::vector<sf::Text> textStats;
	
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
    
    int grid[20][40];
    
    bool exceptionState = false;
    std::string exceptionText;
};

#endif
