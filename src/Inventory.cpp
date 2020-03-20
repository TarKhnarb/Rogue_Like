#include "Inventory.h"
#include <iostream>
#include <assert.h>

Inventory::Inventory(const unsigned index, const unsigned size) : inventory(size, nullptr){


        // Ici l'object représente les différentes stats de bases d'Aspen ou des monstres
    Object basicStats(index); // On récupère les stats de base dans la table
    inventory.at(0) = basicStats; // On ajoute les stats à l'inventaire

}

void Inventory::addObject(const unsigned & id) {

    if(!inventory.empty){
        for(int& x : inventory){

        }
    }


    assert(inventory.size() < inventorySize);
    for(unsigned i = inventoryEquipmentSize; i < inventory.size(); ++i){
        assert(id != inventory[i].getId());
    }
    Object objectToAdd(id);
    inventory.push_back(objectToAdd);
}

void Inventory::removeObjectIndex(const unsigned & index) {
    assert(index < inventory.size() && index > inventoryEquipmentSize); //if index > inventory.size() >> impossible and if index < inventoryEquipmentSize it's an equipment not an Object
    inventory.erase(inventory.begin() + index);
}

void Inventory::removeObjectId(const unsigned & id) {
    
   bool found = false;
   for(unsigned i = 0; i < inventory.size(); ++i){
       if(inventory[i].getId() == id){
           found = true;
           inventory.erase(inventory.begin() + i);
       }
   }
   assert(found == true);//if found == false >> object not found so "id" incorrect
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
