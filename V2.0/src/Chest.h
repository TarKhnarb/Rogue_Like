#ifndef GAME_CHEST_H
#define GAME_CHEST_H

#include "Entity.h"
#include "Inventory.h"

#include <vector>
#include <string>

const unsigned chestSize = 30;

class Chest{

public:

    enum orientation{
        North,
        East,
        South,
        West
    };

    Chest() = default;
    Chest(Entity &, orientation); // Entity pour stoker les objects

    void placeInChest(unsigned); // Index de l'inventaire du joueur
    void addInChest(unsigned); // add un object avec son id

    void removeFromChest(unsigned); // Index de l'inventaire du coffre

    //bool chestIsEmpty(); // A voir si utile ou non

    void loadChest(std::string);
    void saveChest(std::string);

    void display();

private:

    unsigned returnCsvItemSTOI(std::istringstream &);

    orientation orient;
    Inventory chest;
    Entity &hero;
};



#endif