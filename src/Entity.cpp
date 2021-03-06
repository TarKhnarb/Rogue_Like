#include "Entity.h"
Entity::Entity(float x, float y):
        pos(Position<float>(x,y)),
        inventory (Inventory(1, playerStuffSize, playerBagSize)),
        name (inventory.getBasicStatName()),
        money (10000),
        orientation(static_cast<Orientation>(2)){

    getStatistics();
}

Entity::Entity(float x, float y, unsigned id):
        pos(Position<float >(x,y)),
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
                if(attack <= 0)
                    attack = 1;
                break;

            case 2:
                attackSpeed = entityStats.at(i);
                if(attackSpeed <= 0)
                    attackSpeed = 1;
                break;

            case 3:
                maxLife = entityStats.at(i);
                life = maxLife;
                break;

            case 4:
                defence = entityStats.at(i);
                if(defence <= 0)
                    defence = 1;
                break;

            case 5:
                speed = entityStats.at(i);
                if(speed <= 0)
                    speed = 1;
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
        throw std::runtime_error ("Entity::buyObject(" + std::to_string(money) + ") - You do not have enough money to buy this object");

}

void Entity::sellObject(unsigned id, unsigned number) {

    if(inventory.getNumber(id) == number){
        inventory.removeObject(id, number);
        money += number*Object(id).getResalePrice();
    }
    else
        throw std::runtime_error ("Entity::sellObject(" + std::to_string(id) + ") - Not enough item in inventory"); // Erreur a afficher plus tard pour le joueur
}

void Entity::equipObject(unsigned inventoryIndex) {
    inventory.equip(inventoryIndex);
    getStatistics();
}

void Entity::unequipObject(unsigned inventoryIndex) {
    inventory.unequip(inventoryIndex);
    getStatistics();
}

const Object* Entity::getInventoryObject(unsigned index) const {
    return inventory.getObject(index);
}

const Object* Entity::getInventoryStuff(unsigned index) const{
    return inventory.getStuff(index);
}

void Entity::addInventoryObject(unsigned id, unsigned int objectNb) {
    inventory.addObject(id, objectNb);
}

unsigned Entity::addInventoryObjectNb(unsigned id, unsigned objectNb) {
    return inventory.addObjectNb(id, objectNb);
}

void Entity::removeInventoryObject(unsigned index) {
    inventory.removeObject(index);
}

unsigned Entity::removeInventoryObjectNb(unsigned id, unsigned objectNb) {
    return inventory.removeObject(id, objectNb);
}

void Entity::swapObjects(unsigned id1, unsigned id2) {
    inventory.swapBagBag(id1, id2);
}

void Entity::usePotion(unsigned index){
    assert((inventory.getObject(index))->getType() == Object::Type::potion);

    unsigned heal = (inventory.getObject(index)->getStats()).at(3); // récupère la vie a rendre au joueur

    if((life + (int)heal) <= maxLife)
        life += heal;
    else
        life = maxLife;

    inventory.removeObject(inventory.getObject(index)->getId(), 1);
}

bool Entity::entityCanFly()const{
    return fly;
}

unsigned Entity::getOrientation() const{
    return orientation;
}

void Entity::setPosition(float x, float y) {
    pos.setPosition(x, y);
}

int Entity::getPosition(bool xORy) const {
    return pos.getPosition(xORy);
}

void Entity::moveEntity(const float & x, const float & y) {
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
    pos.move(x*(speed/10.0),y*(speed/10.0)); //move player
}

bool Entity::isItOnEntity(unsigned id, unsigned number) {
    if(inventory.getNumber(id) >= number)
        return true;
    else
        return false;
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

std::string Entity::getName() const {
    return name;
}

int Entity::getMoney() const{
    return money;
}

int Entity::getMaxLife() const{
    return maxLife;
}

int Entity::getAttack() const{
    return attack;
}

int Entity::getAttackSpeed() const{
    return attackSpeed;
}

int Entity::getDefence() const{
    return defence;
}

int Entity::getSpeed() const{
    return speed;
}

unsigned Entity::getEntityId() const{
    return inventory.getBasicStatId();
}

bool Entity::getState() const {
    return life !=0;
}

int Entity::getLife() const{
    return life;
}

void Entity::removeLife(int value){
    life -= (int)((float)value*(1.f - defence/100.f));
}

void Entity::setLife(int value){
    life = value;
}

void Entity::setMaxLife(int value){
    life = value;
    maxLife = value;
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
