#ifndef GAME_BASE_H
#define GAME_BASE_H

#include "Entity.h"
#include "Chest.h"

#include <vector>

const  unsigned maxBaseLvl = 3;

class Base{

public:

    Base() = default;
    Base(Entity &, unsigned lvl);

    void upgradeBase();

    void storeInChest(unsigned chestId, unsigned indexI); // Range un object dans le coffre en fonction de son index
    void removeFromChest(unsigned chestId, unsigned indexC); // Récupère l'index d'un coffre et le place dans l'inventaire du joueur, laisse ce qui ne peut être pris dans l'inventaire du joueur

    void display();

private:

    Entity hero;
    std::vector<Chest*> chests;
    unsigned lvl;

};

#endif