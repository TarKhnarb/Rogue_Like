#ifndef GAME_NPC_H
#define GAME_NPC_H

#include "Upgrade.h"
#include "Entity.h"
#include "Object.h"
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ctime>


const unsigned minIdPotion = 47;
const unsigned maxIdPotion = 49;

const unsigned xBlacksmith = 10;
const unsigned yBlacksmith = 10;

const unsigned xWitch = 20;
const unsigned yWitch = 20;

const unsigned xTrader = 30;
const unsigned yTrader = 30;

const unsigned xCrafter = 40;
const unsigned yCrafter = 40;


class Npc{

public:

    enum Action{
        make,
        upgrade,
        potion,
        loot
    };

    enum npcName{
        Blacksmith,
        Witch,
        Trader,
        Crafter
    };

    Npc();

    ~Npc();

        // Blacksmith
    void ActionsBlacksmith(Entity* hero);
    void makeBlacksmith(Entity*, unsigned);
    void upgradeBlacksmith(Entity*, unsigned);

        // Witch
    void ActionsWitch();
    void buyPotion(Entity*, unsigned, unsigned);
    void makePotion(Entity*, unsigned index);

        // Trader
    void ActionsTrader();
    void buyLoot(Entity*, unsigned);
    void sellLoot(Entity*, unsigned);

        // Crafter TODO
    //void ActionsCrafter(Entity hero);
    //void makeCraft(Entity&, unsigned);

private:
    bool CanUpgrade(Entity*, unsigned) const;
    bool CanMake(Entity*, unsigned) const ;
    bool CanMakePotion(Entity*, unsigned) const ;

public:
    void display(Action);

    unsigned returnIndex(const unsigned id, Action) const;


    void testRegression(Entity*, unsigned);

private:

        // Add dans les inventaires des NPC
    void addMake(unsigned id);

    void addUpgrade(unsigned id);

    void addPotion(unsigned id);

    void addPotionMake(unsigned id);

    void addLoot(unsigned id);


    //void addCraft(const unsigned);

private:
    npcName nameB;
    std::vector<Upgrade*> blacksmithInventoryMake;
    std::vector<Upgrade*> blacksmithInventoryUpgrade;

    npcName nameW;
    std::vector<Object*> witchInventory;
    std::vector<Upgrade*> witchInventoryMake;

    npcName nameT;
    std::vector<Object*> traderInventory;

    //npcName nameC;
    //std::vector<Craft*> crafterInventory;
};

#endif
