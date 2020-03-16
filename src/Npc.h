#ifndef PNJ_H
#define PNJ_H

#include "Entity.h"

struct PositionMap
{
    unsigned x, y;
};

class Npc{

public:

    Npc(const std::string& nameOfNpc);
    ~Npc();

    void ActionNpc(int &idObject);
    void sellObject(int idObject);
    void buyObject(int idObject);
    void upgradeObject(int idObject);
    void makeObject(int idObject);

private:

    std::string nameNpc;
  //  Inventory* inventoryNpc;
    std::string nameFileInventory;
    std::string* dialogue;
    PositionMap posNpc;
};

#endif
