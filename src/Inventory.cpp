#include "Inventory.h"
#include <iostream>
#include <assert.h>

Inventory::Inventory() {
    unsigned defaultObject=1;
    Object o(defaultObject);
    inventory.push_back(o);
    calculateStatistics();
}

void Inventory::addObject(const unsigned & id) {
    assert(inventory.size()<inventorySize);
    for(unsigned i=0;i<inventory.size();++i){
        assert(id != inventory[i].getId());
    }
    Object add(id);
    inventory.push_back(add);
    calculateStatistics();
}

void Inventory::removeObjectIndex(const unsigned & index) {
    assert(index < inventory.size()); //if index > inventory.size() >> impossible
    inventory.erase(inventory.begin()+index);
    calculateStatistics();
}

void Inventory::removeObjectId(const unsigned & id) {
   bool found=false;
   for(unsigned i=0;i<inventory.size();++i){
       if(inventory[i].getId()==id){
           found = true;
           inventory.erase(inventory.begin()+i);
       }
   }
   assert(found==true);//if found == false >> object not found so "id" incorrect
   calculateStatistics();
}

void Inventory::calculateStatistics(){
  attack=0, attackSpeed=0, hp=100, defence=0, speed=0, fly=false;

  for(unsigned i=0;i<inventory.size();++i){
      if(inventory[i].getFly() == true)
          fly = true;

      attack += inventory[i].getAttack();
      attackSpeed += inventory[i].getAttackSpeed();
      hp += inventory[i].getHp();
      defence += inventory[i].getDefence();
      speed += inventory[i].getSpeed();
  }
}

/*void Inventory::displayInventory() {
    calculateStatistics(); //peut etre inutile car deja calcule mais evite les beug >> a voir si a eleneve
    for(unsigned i=0;i<inventory.size();++i){
        inventory[i].display();
    }
    std::cout<<"fly : " << fly << " attack : " << attack <<std::endl;
    std::cout<<"defense : " << defence << " speed : " << speed << std::endl;
}*/

bool Inventory::getFly() const {
    return fly;
}

unsigned Inventory::getAttack() const {
    return attack;
}

unsigned Inventory::getAttackSpeed() const {
    return attackSpeed;
}

unsigned Inventory::getHp() const {
    return hp;
}

unsigned Inventory::getDefence() const {
    return defence;
}

unsigned Inventory::getSpeed() const {
    return speed;
}

unsigned Inventory::getResalePrice(const unsigned index) const {
    return inventory[index].getResalePrice();
}