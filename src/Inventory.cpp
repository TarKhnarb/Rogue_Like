#include "Inventory.h"
#include <iostream>
#include <assert.h>

// jouer avec les adresses

Inventory::Inventory(unsigned index, unsigned size) : inventory(size, nullptr){

    assert(testSameType(index, Object::Type::basicStat));
        // Ici l'object représente les différentes stats de bases d'Aspen ou des monstres
    inventory[0] = new Object(index); // On ajoute les stats à l'inventaire
    full = false;
}

Inventory::~Inventory() {
    for(unsigned i = 0; i < inventory.size(); ++i){
        delete inventory[i];
        inventory[i] = nullptr;
    }
}

bool Inventory::testSameType(unsigned id, Object::Type type) {

    Object::Type typeObjectTested = Object(id).getObjectType();

    if(type == typeObjectTested)
        return true;
    else
        return false;
}

bool Inventory::testFullObjectInventory() {

    bool full = true;
    
    for(unsigned i = maxIndexEquipmentInventory; i < inventory.size(); ++i){
        if(full){
            if(inventory[i]){ // Si il y a un object
                full = false;
            }
        }
    }

    return full;
}

bool Inventory::testFullStack(unsigned index) {

    if(inventory[index]){
        if(inventory[index]->getObjectNumber() < inventory[index]->getMaxStack())
            return false;
        else
            return true;
    }
}

int Inventory::numberAddStack(unsigned id, unsigned index) {

    if(inventory[index] && inventory[index]->getId() == id){
        if(testFullStack(index)){
            return 0;
        }
        else{
            return inventory[index]->getMaxStack() - inventory[index]->getObjectNumber();
        }
    }
    else
        return -1;
}

void Inventory::addRecursiveObjectId(unsigned id, unsigned objNumb, unsigned startIndex, bool &done, unsigned &objAdd){

    for(unsigned i = startIndex; i < inventory.size(); ++i){
        if(!done){
            if(!inventory[i]){
                inventory[i] = new Object(id);

                if(objNumb <= inventory[i]->getMaxStack()){
                    inventory[i]->setObjectNumber(objNumb); // L'object n'existe pas donc si on le créer, objectNumber = 1 donc on n'en veut que objNum
                    done = true; // on passe a true
                    objAdd += objNumb;
                }
                else{ // Si plus grand que le max id
                    inventory[i]->setObjectNumber(inventory[i]->getMaxStack()); // on set l'obectNumber a son max
                    objAdd += inventory[i]->getMaxStack();
                    addRecursiveObjectId(id, objNumb - inventory[i]->getMaxStack(), i+1, done, objAdd); // On recommence à essayer de le placer
                }
            }
            else{
                if(inventory[i]->getId() == id){ // l'object nous interesse seulement si il a le bon id

                    if(objNumb + inventory[i]->getObjectNumber() <= inventory[i]->getMaxStack()){ // Si l'objectNumber + objNum peut être ajouter l'ajoute
                        inventory[i]->setObjectNumber(objNumb + inventory[i]->getObjectNumber()); // Car object deja existant et n'est pas plein
                        objAdd += objNumb;
                        done = true;
                    }
                    else{ //Du coup si objNum + max stack > Max stack
                        if(inventory[i]->getObjectNumber() < inventory[i]->getMaxStack()){ // L'object's stack peut encore acceuillir de la place
                            inventory[i]->setObjectNumber(inventory[i]->getMaxStack()); // on rempli le stack
                            addRecursiveObjectId(id, objNumb - (inventory[i]->getMaxStack() - inventory[i]->getObjectNumber()), i+1, done, objAdd); // et on recommence
                            objAdd += inventory[i]->getMaxStack() - inventory[i]->getObjectNumber();
                        }
                        else // l'object a atteint son stack
                            addRecursiveObjectId(id, objNumb, i+1, done, objAdd); // on essaye donc de le placer ailleur
                    }
                }
            }
        }
    }
}

void Inventory::addObjectId(unsigned id, unsigned objNumb, unsigned &objAdd) {

    assert(testFullObjectInventory());

    objAdd = 0; // Pour être sûr

    bool done = false;
    addRecursiveObjectId(id,objNumb, maxIndexEquipmentInventory, done, objAdd);
}

void Inventory::addObjectIndex(unsigned id, unsigned index, unsigned objNumb, unsigned &objAdd) { // ATTENTION lors de l'utilisation
    assert(testFullObjectInventory());

    bool done = false;
    if(!done){
        if(!inventory[index]){
            inventory[index] = new Object(id);
        }
    }

}

void Inventory::deleteObjectIndex(unsigned index) {

    assert(index < inventory.size()); // Si index trop grand

    if(inventory[index]){
        inventory[index] = nullptr;
    }
}

void Inventory::deleteObjectId(unsigned id) { //
    
   bool done = false;
   for(unsigned i = 1; i < inventory.size(); ++i){
       if(!done){
           if(inventory[i]->getId() == id){
               done = true;
               inventory[i] = nullptr;
           }
       }
   }
   assert(done);//if found == false >> object not found so "id" incorrect
}

void Inventory::moveInventoryObject(unsigned indexStart, unsigned indexEnd) {

    assert(indexStart > maxIndexEquipmentInventory-1 || indexEnd > maxIndexEquipmentInventory-1);
    assert(indexStart < maxIndexBasicStatInventory || indexEnd < maxIndexBasicStatInventory);

    if(inventory[indexStart]){ // Si on a bien un object selectionné
        if(!inventory[indexEnd]){ // Si il n'y a pas d'object a l'arrivé
            inventory[indexEnd] = new Object(inventory[indexStart]->getId());
            deleteObjectIndex(indexStart);
        }
        else{
            unsigned wait = inventory[indexEnd]->getId(); // On stock l'id de l'index d'arrivé et on supprime l'object
            deleteObjectIndex(indexEnd);

            inventory[indexEnd] = new Object(inventory[indexStart]->getId()); // On met l'object du debut  l'arrivé
            deleteObjectIndex(indexStart); // On supprime l'object de début et on le remplace par celui de la fin
            inventory[indexStart] = new Object(wait);
        }
    }
}

void Inventory::equipObjectIndex(unsigned index) {
    assert(index > maxIndexEquipmentInventory-1); // Si l'object n'est pas dans la partie object de l'inventory

    if(inventory[index]){ // Si on a bien selectionné un object
        switch (inventory[index]->getObjectType()){
            
            case Object::Type::projectile:
                if(!inventory[1]){ // Si la case est vide
                    inventory[1] = new Object(inventory[index]->getId());
                    deleteObjectIndex(index);
                }
                else{
                    unsigned wait = inventory[index]->getId();
                    deleteObjectIndex(index);

                    inventory[index] = new Object(inventory[1]->getId());
                    deleteObjectIndex(1);
                    inventory[1] = new Object(wait);
                }
                break;

            case Object::Type::armor:
                if(!inventory[2]){ // Si la case est vide
                    inventory[2] = new Object(inventory[index]->getId());
                    deleteObjectIndex(index);
                }
                else{
                    unsigned wait = inventory[index]->getId();
                    deleteObjectIndex(index);

                    inventory[index] = new Object(inventory[2]->getId());
                    deleteObjectIndex(2);
                    inventory[2] = new Object(wait);
                }
                break;

            case Object::Type::amulet:
                if(!inventory[3]){ // Si la case est vide
                    inventory[3] = new Object(inventory[index]->getId());
                    deleteObjectIndex(index);
                }
                else{
                    unsigned wait = inventory[index]->getId();
                    deleteObjectIndex(index);

                    inventory[index] = new Object(inventory[3]->getId());
                    deleteObjectIndex(3);
                    inventory[3] = new Object(wait);
                }
                break;

            default:
                break;
        }
    }
}

void Inventory::unequipObjectIndex(unsigned index, unsigned &objAdd) {
    assert(index < maxIndexEquipmentInventory && index > maxIndexBasicStatInventory-1);
    assert(testFullObjectInventory());

    objAdd = 0;

    addObjectId(inventory[index]->getId(), 1, objAdd); // On rajoute l'object à l'inventaire
    assert(objAdd == 0);
    deleteObjectIndex(index); // On le supprime de l'equipement
}

std::vector<int> Inventory::getAllEntityStats() const{

    std::vector<int> stats;
    std::vector<int> entityStats (6, 0);

  for(unsigned i = 0; i < maxIndexEquipmentInventory; ++i){

      stats = inventory[i]->getStats();

      for(unsigned j = 0; j < statSize; ++j){
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

                  default:
                      break;
              }
          }
      }
  }
    return entityStats;
}

std::vector<int> Inventory::getObjectStats(unsigned index) const {
    return inventory[index]->getStats();
}

void Inventory::displayBasicStat(){
    std::cout << "Basic stats : " << std::endl;
    std::cout << "  N° 0 :" << std::endl;
    inventory[0]->display();
}

void Inventory::displayInventory() {
    std::cout << "Inventory : " << std::endl;
    for(unsigned i = maxIndexEquipmentInventory; i < inventory.size(); i++){
        std::cout << "  N° " << i << " : " << std::endl;
        inventory[i]->display();
    }
}

void Inventory::displayEquipment() {
    std::cout << "Equipment : " << std::endl;
    for(unsigned i = maxIndexBasicStatInventory; i < maxIndexEquipmentInventory; i++){
        std::cout << "  N° " << i << " : " << std::endl;
        inventory[i]->display();
    }
}
