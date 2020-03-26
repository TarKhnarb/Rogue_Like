#include "Entity.h"

Entity::Entity(unsigned &x, unsigned &y){

    inventory = Inventory(1, playerStuffSize, playerBagSize); // 1: Aspen,
    name = inventory.getBasicStatName();

    money = 100;
    pos = new Position<int>(x,y);
    getStatistics();
}

Entity::Entity(unsigned &x, unsigned &y, unsigned id){
    inventory = Inventory(id, 0, monsterBagSize);
    name = inventory.getBasicStatName();
    money = 5;
    pos = new Position<int>(x,y);
    getStatistics();
}

Entity::~Entity() {
    delete pos;
    pos = nullptr;
}

void Entity::getStatistics() {

    std::vector<int>entityStats = inventory.getAllStats();

    for(unsigned i = 0; i < entityStats.size(); ++i){
        switch (i){
            case 0:
                fly = entityStats.at(i);
                break;

            case 1:
                attack = entityStats.at(i);
                break;

            case 2:
                attackSpeed = entityStats.at(i);
                break;

            case 3:
                life = entityStats.at(i);
                break;

            case 4:
                defence = entityStats.at(i);
                break;

            case 5:
                speed = entityStats.at(i);
                break;

            default:
                break;
        }
    }
}

void Entity::buyObject(unsigned id, unsigned objectNum) {

    unsigned thePrice = objectNum * Object(id).getPrice();

    if(thePrice <= money){
        inventory.addObject(id, objectNum); // par defaut en achète un seul
        money -= thePrice;
    }
    else
        std::cout << "You do not have enough money to buy this object" << std::endl;
}

/*
void Entity::sellObjectByIndex(unsigned index, unsigned number) {


    if(inventory.testObjectExist(index) && inventory.getObjectNumber(index) <= number){ // Si l'object selectionné existe et a le bon nombre pour être vendu
        unsigned resalePrice = inventory.getObjectResalePrice(index);
        inventory.removeObjectIndex(index, number);

        if(!inventory.testObjectExist(index)){ // Seulement si l'object à été supprimé
            money += number*resalePrice;
        }
    }
    else{
        std::cout << "Vous n'avez pas assez d'exemplaires sur vous" << std::endl;
    }
}*/

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

    inventory.display();
}
