#ifndef MENU_MAP_H
#define MENU_MAP_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
#include "Collider.h"
#include "Archetype.h"

class map {
public :
    /**
     * @brief constructor
     */
    map();
    ~map();

    /**
     * @brief execution procedure
     */
    void run();

private:

    /**
     * @brief inits the rectangleShape vector and texture vector
     */
    void init();

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

    void loadRectangleShape(std::string name);
    sf::RectangleShape getRectangleShape(const std::string&);

    /**
     * @brief the animations of the player according to whether the sprite is walking up, down, left, right
    */
    void loadAnimation();

    void setMapRectangleShape();
    void setNpcRectangleShape();
    void setWallRectangleShape();
    void setAllRectangleShape();

    void setInventoryStats(); // pour afficher les stats du joueur
    sf::Color setItemLvl(unsigned);
    void setInventoryItem(); // bag et stuff
    //void setChestItem();

    void setScrollingMenu();
    void updateScrollingMenu();
    void updateMoveObject();
    void updateInventory();
    //void drawChestInventory();
    void drawPlayerInventory();

    void updateException();
    void drawException();

    /**
     * @brief check for collisions
    */
    void entityCollision();

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

    /**
     * @brief calls the correct functions when player going up,down...
    */
    void update(sf::Time);

    /**
     * @brief render
     */
    void render();

private :

    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;
    bool noKeyWasPressed = true;

    Position<float> posAspen;
    Entity Aspen;
    float PlayerSpeed;

    std::map<std::string, sf::Texture*> textures;
    std::map<std::string, sf::Sprite> sprites;
    std::map<std::string, sf::RectangleShape*> rectangleShapes;

        // Map en arrière plan
    sf::Texture textMainMap;
    sf::RectangleShape rectBackMap;
    sf::RectangleShape rectMainMap;
    sf::RectangleShape doorBase;
    sf::RectangleShape doorDonjon;
    //sf::Color co(148, 223, 231);

    std::vector<sf::RectangleShape> npcR;
    std::vector<sf::RectangleShape> wall;

    Collider wallsCollider;
    Collider baseDoorCollider;
    Collider npcCollider;

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

    bool exceptionState = false;
    std::string exceptionText;

    Archetype arch;

    unsigned size=20;
    float dist=10;
    unsigned X=1280,Y=720;

    sf::View view;

    //enlever plus tard
    sf::RenderWindow mWindow;
    sf::Event event;
};


#endif //MENU_MAP_H
