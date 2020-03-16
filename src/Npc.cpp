#include "Npc.h"
/*
Npc::Npc(const std::string& nameOfNpc){
    switch(nameOfNpc) {
        case 1 :    //Npc : forgeron
        {
            nameNpc = nameOfNpc;
            nameFileInventory = "..obj/inventory/blacksmith.txt";
            inventory.inventory(50, 7, nameFileInventory);

        }
        case 2 :    //Npc : sorciere
        {
            nameNpc = nameOfNpc;
            nameFileInventory = "..obj/inventory/witch.txt";
            inventoryNpc.inventory(50, 7, nameFileInventory);
        }
        case 3 :    //Npc : marchand
        {
            nameNpc = nameOfNpc;
            nameFileInventory = "..obj/inventory/crafter.txt";
            inventoryNpc.inventory(50, 7, nameFileInventory);
        }
    }
}







void Npc::ActionNpc(int &idObject){
    switch(){
        case 1 :    //Perso veut acheter un objet au marchand
        {
            ...;
        }
        case 2 :    //Perso veut vendre un objet au marchand
        {
            ...;
        }
        case 3 :    //Perso peut fabriquer un objet chez le forgeron
        {
            ...;
        }
        case 4 :    //Perso veut ameliorer un objet chez le forgeron
        {
            ...;
        }
        case 5 :    //Perso veut acheter une potion chez la sorcière
        {

        }
        case 6 :    //Perso veut fabriquer une potion chez la sorcière
        {

        }

    }
}

void Npc::sellObject(int &idObject, character& perso)
{
    //il faut chercher l'objet
    if((!fullOrNot)||(perso.argent >= ))
    {

    }

}

void Npc::buyObject(int &idObject, unsigned nbCopy)
{
    unsigned price;
    //trouver l'objet dans l'inventaire pour savoir le prix
    for(int i = 0; i < inventory.size; i++)
    {
        if(inventory->table[i][0] == idObject)
        {
            price = inventory->table[i][???]; //mettre la colonne qui contient le prix
        }
    }
    //enleve les objets de l'inventaire du perso
}

void Npc::upgradeObject(int idObject)
{

}

void Npc::makeObject(int idObject)
{

}

*/