#ifndef GAME_CHEST_H
#define GAME_CHEST_H

#include "Entity.h"
#include "Inventory.h"

#include <vector>

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

    void removeFromChest(unsigned); // Index de l'inventaire du coffre

    //bool chestIsEmpty(); // A voir si utile ou non

    void display();

private:

    orientation orient;
    Inventory chest;
    Entity hero;
};



#endif