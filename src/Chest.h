#ifndef GAME_CHEST_H
#define GAME_CHEST_H

#include "Entity.h"
#include "Inventory.h"

#include <vector>
#include <string>

const unsigned chestSize = 20;

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
    ~Chest() = default;

    void addInChest(unsigned); // add un object avec son id

    void placeInChest(unsigned); // Index de l'inventaire du joueur
    unsigned removeFromChest(unsigned); // Index de l'inventaire du coffre et renvoie l'id de l'objet supprimé

    //bool chestIsEmpty(); // A voir si utile ou non

    void loadChest(std::string);
    void saveChest(std::string);

    const Object* getItem(unsigned) const;

    void display();

private:

    unsigned returnCsvItemSTOI(std::istringstream &);

    orientation orient;
    Inventory chest;
    Entity &hero;
};

#endif
