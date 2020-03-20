#include "Inventory.h"
#include <iostream>
#include <assert.h>



Inventory::Inventory(const unsigned index, const unsigned size) : inventory(size, nullptr){

    assert(testSameType(index, objectType::basicStat))
        // Ici l'object représente les différentes stats de bases d'Aspen ou des monstres
    inventory[0] = new Object(index); // On ajoute les stats à l'inventaire

}

Inventory::~Inventory() {
    for(unsigned i = 0; i < inventory.max_size(); i ++){
        delete inventory[i];
        inventory[i] = nullptr;
    }
}

bool Inventory::testSameType(const unsigned id, objectType type) {

    objectType typeObjectTested = Object(id).getObjectType();

    if(type == typeObjectTested)
        return true;
    else
        return false;
}

bool Inventory::testFullObjectInventory() {
    bool test = true;
    
    for(unsigned i = maxIndexEquipmentInventory; i < inventory.max_size(); i++){
        if(test){
            if(!inventory[i]){ // Si il n'y a pas d'object et qu'aucune place n'a été trouvée
                test = !test;
            }
        }
    }

    return test;
}

void Inventory::addObjectId(const unsigned & id) {

    assert(!testFullObjectInventory());

    bool done = false;

    for(unsigned i = maxIndexEquipmentInventory; i < inventory.max_size(); i++){
        if(!done){
            if(!inventory[i]){
                done = !done;
                inventory[i] = new Object(id);
            }
        }
    }
}

void Inventory::deleteObjectIndex(const unsigned & index) {

    assert(index < inventory.max_size) // Si index trop grand

    if(inventory[index]){
        inventory[index] = nullptr;
    }
}

void Inventory::deleteObjectId(const unsigned & id) { // ATTENTION lors de l'utilisation, si plusieurs stack de l'object ou objects identiques peut poser problème
    
   bool done = false;
   for(unsigned i = 1; i < inventory.max_size(); ++i){
       if(!done){
           if(inventory[i].getId() == id){
               done = !done;
               inventory[i] = nullptr;
           }
       }
   }
   assert(found);//if found == false >> object not found so "id" incorrect
}

void Inventory::moveInventoryObject(const unsigned & indexStart, const unsigned indexEnd) {

    assert(indexStart > maxIndexEquipmentInventory-1 || indexEnd > maxIndexEquipmentInventory-1);
    assert(indexStart < maxIndexBasicStatInventory || indexEnd < maxIndexBasicStatInventory);

    if(inventory[indexStart]){ // Si on a bien un object selectionné
        if(!inventory[indexEnd]){ // Si il n'y a pas d'object a l'arrivé
            inventory[indexEnd] = new Object(inventory[indexStart].getId());
            deleteObjectIndex(indexStart);
        }
        else{
            unsigned wait = inventory[indexEnd].getId(); // On stock l'id de l'index d'arrivé et on supprime l'object
            deleteObjectIndex(indexEnd);

            inventory[indexEnd] = new Object(inventory[indexStart].getId()); // On met l'object du debut  l'arrivé
            deleteObjectIndex(indexStart); // On supprime l'object de début et on le remplace par celui de la fin
            inventory[indexStart] = new Object(wait);
        }
    }
}

void Inventory::equipObjectIndex(const unsigned & index) {
    assert(index > maxIndexEquipmentInventory-1) // Si l'object n'est pas dans la partie object de l'inventory

    if(inventory[index]){ // Si on a bien selectionné un object
        switch (inventory[index].getObjectType()){
            
            case objectType::projectile:
                if(!inventory[1]){ // Si la case est vide
                    inventory[1] = new Object(inventory[index].getId());
                    deleteObjectIndex(index);
                }
                else{
                    unsigned wait = inventory[index].getId();
                    deleteObjectIndex(index);

                    inventory[index] = new Object(inventory[1].getId());
                    deleteObjectIndex(1);
                    inventory[1] = new Object(wait);
                }
                break;

            case objectType::armor:
                if(!inventory[2]){ // Si la case est vide
                    inventory[2] = new Object(inventory[index].getId());
                    deleteObjectIndex(index);
                }
                else{
                    unsigned wait = inventory[index].getId();
                    deleteObjectIndex(index);

                    inventory[index] = new Object(inventory[2].getId());
                    deleteObjectIndex(2);
                    inventory[2] = new Object(wait);
                }
                break;

            case objectType::amulet:
                if(!inventory[3]){ // Si la case est vide
                    inventory[3] = new Object(inventory[index].getId());
                    deleteObjectIndex(index);
                }
                else{
                    unsigned wait = inventory[index].getId();
                    deleteObjectIndex(index);

                    inventory[index] = new Object(inventory[3].getId());
                    deleteObjectIndex(3);
                    inventory[3] = new Object(wait);
                }
                break;
        }
    }
}

void Inventory::unequipObjectIndex(const unsigned & index) {
    assert(index < maxIndexEquipmentInventory && index > maxIndexBasicStatInventory-1);
    assert(!testFullObjectInventory());

    addObjectId(inventory[index].getId()); // On rajoute l'object à l'inventaire
    deleteObjectIndex(index); // On le supprime de l'equipement
}

std::vector<int> Inventory::getAllStats() const{

    std::vector<int> stats;
    std::vector<int> entityStats (6, 0);

  for(unsigned i=1;i<inventory.size();++i){

      stats = inventory[i].getStats();

      for(int j = 0; j < statSize; j++){
          if(stats[j] >= 0) {
              switch (j) {
                  case 0:
                      if (stats[j] == 1)
                          entityStats[j] = 1;
                      break;

                  case 1:
                      entityStats[j] += stats[j];
                      break;

                  case 2:
                      entityStats[j] += stats[j];
                      break;

                  case 3:
                      entityStats[j] += stats[j];
                      break;

                  case 4:
                      entityStats[j] += stats[j];
                      break;

                  case 5:
                      entityStats[j] += stats[j];
                      break;
              }
          }
      }
  }
}

std::vector<unsigned int> Inventory::getEntityStats() const {
    return entityStats;
}

std::vector<unsigned int> Inventory::getObjectStats(const unsigned index) const {
    return inventory[index].getStats();
}

/*void Inventory::displayInventory() {
    calculateStatistics(); //peut etre inutile car deja calcule mais evite les beug >> a voir si a eleneve
    for(unsigned i=0;i<inventory.size();++i){
        inventory[i].display();
    }
    std::cout<<"fly : " << fly << " attack : " << attack <<std::endl;
    std::cout<<"defense : " << defence << " speed : " << speed << std::endl;
}*/
