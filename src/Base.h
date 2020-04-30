#ifndef GAME_BASE_H
#define GAME_BASE_H

#include "Entity.h"
#include "Chest.h"

#include <vector>
#include <fstream>

const unsigned maxBaseLvl = 3;

class Base{

public:

    Base() = default;

    /**
     * @brief Constuct Base according player information and base level
     * @param Entity* Reference to player entity
     * @param level unsigned (1 ->3) Reference to the level of upgrade of the base
     */
    Base(Entity *, unsigned level);
    ~Base();

    /**
     * @brief Upgrade the base of 1 level
     */
    void upgradeBase();

    /**
     * @brief Store objects in a chest according chest id and player inventory index
     * @param chestId id of the chest to fill
     * @param indexI index of the object at add to chest
     */
    void storeInChest(unsigned chestId, unsigned indexI); // Range un object dans le coffre en fonction de son index

    /**
     * @brief Remove objects from a chest according chest id and chest index
     * @param chestId id of the chest to remove object
     * @param indexC index of the Chest of the object to remove
     */
    void removeFromChest(unsigned chestId, unsigned indexC); // Récupère l'index d'un coffre et le place dans l'inventaire du joueur, laisse ce qui ne peut être pris dans l'inventaire du joueur

    /**
     * @brief Save chests of the base
     */
    void saveChests();

    /**
     * @brief Load chests of the base
     */
    void loadChests();

    void display();

private:

    Entity* hero;
    std::vector<Chest*> chests;
    unsigned lvl;

};

#endif
