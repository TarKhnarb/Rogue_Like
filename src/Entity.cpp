#include "Entity.h"

#include <string>
#include <iostream>


Entity::Entity(const unsigned & x, const unsigned & y,std::string n){
    name = n;
    money=100;
    life=100;
    pos = new Position<int>(x,y);
    getStatistics();
}

Entity::Entity(const unsigned &x, const unsigned & y, const unsigned & l, std::string n){
    name = n;
    life = l;
    pos = new Position<int>(x,y);
}

Entity::~Entity() {
    //nothing yet
}

void Entity::getStatistics() {
    attack = inventory->getAttack();
    attackSpeed = inventory->getAttackSpeed();
    life += inventory->getHp();
    defence = inventory->getDefence();
    speed = inventory->getSpeed();
    fly = inventory->getFly();
}

//have to be redone
void Entity::buyObject(const unsigned & id) {
    //unsigned thePrice = getPrice(inventory->getUsedSpace()-1);
    //if(thePrice <= money){
        inventory->addObject(id);
        //money-=thePrice;
        getStatistics();
    //}else{
        std::cout<<"You do not have enough money to buy this object" <<std::endl;
    //}
}

void Entity::sellObjectByIndex(const unsigned & index) {
    unsigned resalePrice = inventory->getResalePrice(index);
    inventory->removeObjectIndex(index);
    money += resalePrice;
    getStatistics();
}

bool Entity::entityCanFly()const{
    return fly;
}

void Entity::moveEntity(const unsigned & x, const unsigned & y) {
    pos->move(x*(speed/10),y*(speed/10));
}

void Entity::displayEntity() {
    std::cout << "Name : " << name << std::endl;
    std::cout << "Money : " << money << std::endl;
    std::cout << "life : " << life << std::endl;
    std::cout << "Attack : " << attack << std::endl;
    std::cout << "Defence : " << defence << std::endl;
    std::cout << "Speed : " << speed << std::endl;
    std::cout << "fly : " << fly << std::endl;
    std::cout << "X :" << pos->getPosition(true) << " Y : " << pos->getPosition(false) << std::endl;
    //inventory->displayInventory();
}
