#include "Entity.h"
Entity::Entity(unsigned x, unsigned y):
        pos(Position<int>(x,y)),
        inventory (Inventory(1, playerStuffSize, playerBagSize)),
        name (inventory.getBasicStatName()),
        money (10000),
        orientation(static_cast<Orientation>(2)){

    getStatistics();
}

Entity::Entity(unsigned &x, unsigned &y, unsigned id):
        pos(Position<int>(x,y)),
        inventory (Inventory(id, 0, monsterBagSize)),
        name (inventory.getBasicStatName()),
        money (5),
        orientation(static_cast<Orientation>(2)){

    getStatistics();
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

void Entity::equipObject(unsigned inventoryIndex) {
    inventory.equip(inventoryIndex);
}

void Entity::unequipObject(unsigned inventoryIndex) {
    inventory.unequip(inventoryIndex);
}

bool Entity::entityCanFly()const{
    return fly;
}

unsigned Entity::getOrientation() const{
    return orientation;
}

void Entity::setPosition(int x, int y) {
    pos.setPosition(x, y);
}

int Entity::getPosition(bool xORy) const {
    return pos.getPosition(xORy);
}

void Entity::moveEntity(const int & x, const int & y) {
    //change orientation of entity
    if(std::abs(x) > std::abs(y)){ //the entity moves on x axis
        if(x > 0){ //the entity goes positive on x axis >> going down
            orientation = static_cast<Orientation>(1);
        }else{
            orientation = static_cast<Orientation>(3);
        }
    }else{ //the entity moves on y axis 
        if(y > 0){
             orientation = static_cast<Orientation>(2);
        }else{
             orientation = static_cast<Orientation>(0);
        }
    }
    //pos->move(x*(speed/10),y*(speed/10)); //move player
    pos.move(x,y);
}

bool Entity::isItOnEntity(unsigned id, unsigned number) {
    return inventory.isItInInventory(id, number);
}

bool Entity::testIndex(unsigned index) {
    if(inventory.getObject(index))
        return true;
    else
        return false;
}

bool Entity::inventoryEmpty() {
    return inventory.isEmpty();
}

void Entity::displayEntity() {
    std::cout << "      Aspen " << std::endl;
    std::cout << "          Money : " << money << std::endl;
    std::cout << "          life : " << life << std::endl;
    std::cout << "          Attack : " << attack << std::endl;
    std::cout << "          Defence : " << defence << std::endl;
    std::cout << "          Speed : " << speed << std::endl;
    if(fly)
        std::cout << "          fly : " << "Yes" << std::endl;
    else
        std::cout << "          fly : " << "No" << std::endl;

    //std::cout << "  X :" << pos.getPosition(true) << ", Y : " << pos.getPosition(false) << std::endl;

    inventory.display();
}
