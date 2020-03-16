#ifndef PNJ_H
#define PNJ_H

#include "Entity.cpp.h"

struct position
{
    unsigned x, y;
};

class Npc{

public:

    Npc(const string& nameOfNpc);
    ~Npc();

    void ActionNpc(int idObject);
    void sellObject(int idObject);
    void buyObject(int idObject);
    void upgradeObject(int idObject);
    void makeObject(int idObject);

private:

    string nameNpc;
    Inventory* inventoryNpc;
    string nameFileInventory;
    string* dialogue;
    Position posNpc;
};

#endif
