#include "Chest.h"

Chest::Chest(Entity &aspen, orientation chestOrient): orient (chestOrient), chest (Inventory(1, 0, chestSize)), hero (aspen){}

void Chest::placeInChest(unsigned indexI) { // Prend l'index du Bag du joueur, PEUT ETRE UN PEU LEGER, A TESTER SI SUFFISANT

    unsigned objId = hero.getInventoryObject(indexI)->getId();
    unsigned objNb = hero.getInventoryObject(indexI)->getObjectNumber();
    unsigned objAdd = chest.addObjectNb(objId, objNb);

    if(objAdd == 0){
        hero.removeInventoryObject(indexI);
    }
    else{
        hero.removeInventoryObjectNb(objId, objNb-objAdd);
    }
}

void Chest::removeFromChest(unsigned indexC) { // Prend l'index du coffre, PEUT ETRE UN PEU LEGER, A TESTER SI SUFFISANT

    unsigned objId = chest.getObject(indexC)->getId();
    unsigned objNb = chest.getObject(indexC)->getObjectNumber();
    unsigned objAdd = hero.addInventoryObjectNb(objId, objNb);

    if(objAdd == 0){
        chest.removeObject(indexC);
    }
    else{
        chest.removeObject(objId, objNb-objAdd);
    }
}

void Chest::display() {
    chest.display();
}
