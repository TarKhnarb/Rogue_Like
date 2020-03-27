#include "Npc.h"
/*

Npc::Npc(){

    blacksmith = Entity(xBlacksmith, yBlacksmith, 0, idBlacksmith);
    witch = Entity(xWitch, yWitch, 0, idWitch);
    crafter = Entity(xCrafter, yCrafter, 0, idCrafter);
    trader = Entity(xTrader, yTrader, 0, idTrader);
    std::vector<Upgrade*> blacksmithInventory;
}


void ActionsBlacksmith(Entity &hero)
{

}

void ActionsWitch(Entity &hero)
{

}

void ActionsCrafter(Entity &hero)
{

}

void ActionsTrader(Entity &hero)
{

}

/*
void Npc::ActionBlacksmithFabriquer(Entity &hero){ // Crafter du stuff ou l'améliorer
   */ /*
     * Blacksmith a :
     *      un inventaire d'Upgrades n°1 (vector de la classe Upgrade pour stocker les crafts)
     *      un inventaire d'Upgrades n°2 (vector de la classe Upgrade pour stocker les crafts)
     *      un inventaire d'Object (variable d'entity)
     *
     * Lorsque le joueur accède au blacksmith, la première fenêtre sera les crafts, du coup on charge dans
     * l'inventaire d'Upgrade n°1 tous les craft (<=> id des plus bas niveaux de chaque stuff)
     *
     * Si le joueur accède aux améliorations, on parcourt l'inventaire du joueur a la recherche d'object de Type
     * qui peuvent être améliorés et on récupère leur id pour mettre les upgrades correspondantes dans l'inventaire
     * d'Upgrade n°2 du blacksmith
     *
     * On ne vide l'inventaire n°2 seulement lorque le joueur part du blacksmith
     *
     * pour crafter/Ameliorer, le joueur selectionne un case de l'inventaire affiché
     */
/*
    for(unsigned i = 0; i < maxUpgrades; i++){
        blacksmith.
    }
}

void Npc::sellObject(int & idObject, Entity & perso)
{
    assert(inventory(testObjectExist(id));
    Object * NewObject = Object(idObject);
    if((!inventory. testFull())||(perso->money >= NewObject->getPrice())) //check if perso's inventory is full and perso has enough money
    {
        perso->inventoryaddRecursiveObjectId(id,1,?,?,?);   //paramètres!!!!!!!!!!
    }
    delete NewObject;
}

void Npc::buyObject(int &idObject, unsigned nbCopy, Entity& perso)
{
    for(i = 0; i < nbCopy; i++) {
        assert(perso->inventory(testObjetExist(id)));
        perso->money += NewObject->getResalePrice();
        perso->inventory.deleteObjectId()
    }
}

void Npc::upgradeObject(int idObject)
{
    //find the object's Upgrade
}

void Npc::makeObject(int idObject)
{
    // pas besoin de faire
}
*/
