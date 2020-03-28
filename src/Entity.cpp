#include "Entity.h"
#include <math.h>

Entity::Entity(unsigned &x, unsigned &y){

    inventory = Inventory(1, playerStuffSize, playerBagSize); // 1: Aspen,
    name = inventory.getBasicStatName();
    orientation = static_cast<Orientation>(0);
    money = 100;
    pos = new Position<int>(x,y);
    getStatistics();
}

Entity::Entity(unsigned &x, unsigned &y, unsigned id){
    inventory = Inventory(id, 0, monsterBagSize);
    name = inventory.getBasicStatName();
    orientation = static_cast<Orientation>(2);
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
        throw std::runtime_error {"Entity::buyObject(" + std::to_string(money) + ") - You do not have enough money to buy this object"};

}

void Entity::sellObject(unsigned id, unsigned number) {

    if(inventory.getNumber(id) == number){
        inventory.removeObject(id, number);
        money += number*Object(id).getResalePrice();
    }
    else
        throw std::runtime_error {"Entity::sellObject(" + std::to_string(id) + ") - Not enough item in inventory"}; // Erreur a afficher plus tard pour le joueur
}

bool Entity::entityCanFly()const{
    return fly;
}

unsigned Entity::getOrientation() const{
    return orientation;
}

void Entity::moveEntity(int & x, int & y) {
    //change orientation of entity
    if(std::abs(x) > std::abs(y)){ //the entity moves on x axis
        if(x > 0){ //the entity goes positive on x axis >> going down
            orientation = static_cast<Orientation>(1);
        }else{
            orientation = static_cast<Orientation>(0);
        }
    }else{ //the entity moves on y axis 
        if(y > 0){
             orientation = static_cast<Orientation>(3);
        }else{
             orientation = static_cast<Orientation>(4);
        }
    }
    pos->move(x*(speed/10),y*(speed/10)); //move player
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
