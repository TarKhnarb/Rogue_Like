#ifndef NPC_H
#define NPC_H

#include "Entity.h"

const unsigned idBlacksmith = 1;
const unsigned xBlacksmith = 10;
const unsigned yBlacksmith = 10;

const unsigned idWitch = 2;
const unsigned xWitch = 20;
const unsigned yWitch = 20;

const unsigned idTrader = 3;
const unsigned xTrader = 30;
const unsigned yTrader = 30;

const unsigned idCrafter = 4;
const unsigned xCrafter = 40;
const unsigned yCrafter = 40;

class Npc{

public:

    /**
     * @brief contructs a npc ....
     * @param[in/out] string : nameOfFile ????
     **/
    Npc();

    /**
     * @brief function executate npc's actions
     * @param[in] id :  the id of the object, [in/out] entity : aspen
     **/
    void ActionBlacksmith(Entity &hero);

    /**
     * @brief Aspen buy an object  veut acheter un objet au marchand//à la sorcière
     * @param[in] id :  the id of the object, [in/out] entity : aspen
     **/
    void sellObject(Entity&);

    void buyObject(int idObject);
    void upgradeObject(int idObject);
    void makeObject(int idObject);

private:

    /*
    std::string nameNpc;
    Inventory inventoryNpc;
    std::string nameFileInventory;

    PositionMap posNpc;
     */

    std::string* dialogue;
    //std::vector<Upgrade*> blacksmithInventory;
};

#endif
