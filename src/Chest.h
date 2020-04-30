#ifndef GAME_CHEST_H
#define GAME_CHEST_H

#include "Entity.h"
#include "Inventory.h"

#include <vector>
#include <string>

const unsigned chestSize = 20;

class Chest{

public:

    /**
     * @brief Different orientation of a chest
     */
    enum orientation{
        North,
        East,
        South,
        West
    };

    Chest() = default;

    /**
     * @brief Construct a chest according the player entity and orientation of the chest
     * @param Entity* Reference on the player
     * @param orientation Reference to the chest orientation
     */
    Chest(Entity *, orientation); // Entity pour stoker les objects
    ~Chest() = default;

    /**
     * @brief Add an object to the chest according id of the object
     * @param unsigned object id
     */
    void addInChest(unsigned); // add un object avec son id

    /**
     * @brief Add an object to the chest according index of player inventory
     * @param unsigned Player inventory index
     */
    void placeInChest(unsigned); // Index de l'inventaire du joueur

    /**
     * @brief Remove an object from the chest according index of chest inventory
     * @param unsigned Chest inventory index
     */
    unsigned removeFromChest(unsigned); // Index de l'inventaire du coffre et renvoie l'id de l'objet supprimé

    //bool chestIsEmpty(); // A voir si utile ou non

    /**
     * @brief Load objects in a chest from a file
     * @param std::string File name
     */
    void loadChest(std::string);

    /**
     * @brief Save objects from a file in a Chest
     * @param std::string File name
     */
    void saveChest(std::string);

    /**
     * @brief Return a referenc on an object according index of Chest inventory
     * @return Object* Reference on Object class
     */
    const Object* getItem(unsigned) const;

    /**
     * @brief Dispay in terminal objects from chest
     */
    void display();

private:

    unsigned returnCsvItemSTOI(std::istringstream &);

    orientation orient;
    Inventory chest;
    Entity *hero;
};

#endif
