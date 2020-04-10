#ifndef GAME_NPC_H
#define GAME_NPC_H

#include "Upgrade.h"
#include "Entity.h"
#include <vector>


const unsigned idBlacksmith = 1;
const unsigned xBlacksmith = 10;
const unsigned yBlacksmith = 10;


/*
const unsigned idWitch = 2;
const unsigned xWitch = 20;
const unsigned yWitch = 20;

const unsigned idTrader = 3;
const unsigned xTrader = 30;
const unsigned yTrader = 30;

const unsigned idCrafter = 4;
const unsigned xCrafter = 40;
const unsigned yCrafter = 40;
*/

class Npc{

public:

    Npc();

    void ActionsBlacksmith(Entity& hero);

    void display(const std::string);
/*
    void ActionsWitch(Entity &hero);


   void ActionsCrafter(Entity &hero);


    void ActionsTrader(Entity &hero);


    void sellObject(Entity&);

    void buyObject(int idObject);
    void upgradeObject(int idObject);
    void makeObject(int idObject);
*/
    void display(std::string, int);

private:
    std::string nameB;
    std::vector<Upgrade*> blacksmithInventoryMake;
    std::vector<Upgrade*> blacksmithInventoryUpgrade;
};

#endif
