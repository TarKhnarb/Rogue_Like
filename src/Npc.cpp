#include "Npc.h"
#include "Entity.h"

Npc::Npc():
        nameB(npcName::Blacksmith),
        nameW(npcName::Witch),
        nameT(npcName::Trader){}
        //nameC(npcName::Crafter)
    //dialogue

Npc::~Npc() {
    for(unsigned i = 0; i < blacksmithInventoryMake.size(); ++i){
		if (blacksmithInventoryMake[i])
			delete blacksmithInventoryMake[i];
        blacksmithInventoryMake[i] = nullptr;
    }

    for(unsigned i = 0; i < blacksmithInventoryUpgrade.size(); ++i){
		if (blacksmithInventoryUpgrade[i])
			delete blacksmithInventoryUpgrade[i];
        blacksmithInventoryUpgrade[i] = nullptr;
    }

    for(unsigned i = 0; i < witchInventory.size(); ++i){
		if (witchInventory[i])
			delete witchInventory[i];
        witchInventory[i] = nullptr;
    }
   /*
    for(unsigned i = 0; i < crafterInventory.size(); ++i){
        delete crafterInventory[i];
        crafterInventory[i] = nullptr;
    }*/
}

    // Blacksmith
void Npc::ActionsBlacksmith(Entity* hero){ // A appeler à chaque fois que l'on parle au NPC

    if(blacksmithInventoryUpgrade.size() != 0){
        for(auto &b : blacksmithInventoryUpgrade){ // On nettoie les upgrades possible -> permet de prendre en compte les objects present sur le joueur au moment où il interpel le joueur

            if(b)
                delete b;
            b = nullptr;
        }
    }

    for(unsigned i = minIdEquipment; i < minIdPotion; i+=3){
        addMake(i);                             // tous les premier niveaux
        if(hero->isItOnEntity(i,1))
            addUpgrade(i+1);
        if(hero->isItOnEntity(i+1,1))
            addUpgrade(i+2);
    }
}

void Npc::makeBlacksmith(Entity *hero, unsigned index){

    if(CanMake(hero, blacksmithInventoryMake[index]->getId())) {
        std::vector<unsigned> requiredResources = blacksmithInventoryMake[index]->getResource();

        for(unsigned i = 1; i < requiredResources.size(); i+=2){
            if(requiredResources[i] != 0)
                hero->removeInventoryObjectNb(requiredResources[i], requiredResources[i+1]); // on enlève les object de l'inventaire du joueur
        }

        hero->buyObject(blacksmithInventoryMake[index]->getId(), 1); // pace l'object dans l'inventaire du joueur et le fait payer

    }
    else
        throw std::logic_error ("Cannot make this object, not enought items");
}

void Npc::upgradeBlacksmith(Entity *hero,unsigned index){

    if(CanUpgrade(hero, blacksmithInventoryUpgrade[index]->getId())) {
        std::vector<unsigned> requiredResources = blacksmithInventoryUpgrade[index]->getResource();

        for(unsigned i = 1; i < requiredResources.size(); i+=2){
            if(requiredResources[i] != 0)
                hero->removeInventoryObjectNb(requiredResources[i], requiredResources[i+1]);
        }
        hero->buyObject(blacksmithInventoryUpgrade[index]->getId(), 1);
    }
    else
        throw std::logic_error {"Cannot upgrade this object, not enought items"};
}

    // Witch
void Npc::ActionsWitch(){ // A appeler dans le constructeur de Map seulement
    for(unsigned i = minIdPotion; i < maxIdPotion+1; i++){
        addPotion(i);
        addPotionMake(i);
    }
}

void Npc::buyPotion(Entity *hero, unsigned index, unsigned Nb) {
    hero->buyObject(witchInventory[index]->getId(), Nb);
}

void Npc::makePotion(Entity *hero, unsigned index) {

    if(CanMakePotion(hero, witchInventoryMake[index]->getId())) {
        std::vector<unsigned> requiredResources = witchInventoryMake[index]->getResource();

        for(unsigned i = 1; i < requiredResources.size(); i+=2){
            if(requiredResources[i] != 0)
                hero->removeInventoryObjectNb(requiredResources[i], requiredResources[i+1]);
        }

        hero->buyObject(witchInventoryMake[index]->getId(), 1);
    }
    else
        throw std::logic_error("Cannot make this potion, not enought items");
}

    // Trader
void Npc::ActionsTrader(){ // A appeler dans le constructeur de Map uniquement
    srand(time(nullptr));
    for(unsigned i = 0; i < 4; i++){
        addLoot((rand()%15) + 50); // item entre 50 et 64
    }
}

void Npc::buyLoot(Entity *hero, unsigned index){
    hero->buyObject(traderInventory[index]->getId(), 1);
    traderInventory[index] = nullptr; // On donne la possibilité de n'acher qu'une seul fois l'object on refresh le shop en resortant du donjon
}

void Npc::sellLoot(Entity *hero, unsigned index) {
    hero->sellObject(index, hero->getInventoryObject(index)->getObjectNumber()); // vent tous les objets de la case
}

/*  // Crafter TODO
void Npc::ActionsCrafter(Entity hero){}

void Npc::makeCraft(Entity &hero, unsigned index){}
*/

void Npc::addMake(unsigned id){
    //assert(id > minIdEquipment-1 && id < maxIdEquipement);
    std::cout << id << std::endl;
    blacksmithInventoryMake.push_back(new Upgrade(id));
}

void Npc::addUpgrade(unsigned id){
    blacksmithInventoryUpgrade.push_back(new Upgrade(id));
}

void Npc::addPotion(unsigned id){
    witchInventory.push_back(new Object(id));
}

void Npc::addPotionMake(unsigned id){
    witchInventoryMake.push_back(new Upgrade(id));
}

void Npc::addLoot(unsigned id){
    traderInventory.push_back(new Object(id));
}

bool Npc::CanUpgrade(Entity *hero, unsigned index){
    bool Can = true;
    std::vector<unsigned> Need = blacksmithInventoryUpgrade[index]->getResource();

    for(unsigned i = 1; i < Need.size(); i+=2){
        if(Can && Need[i] != 0)
            if(!(hero->isItOnEntity(Need[i],Need[i+1])))
                Can = false;
    }
    return Can;
}

bool Npc::CanMake(Entity *hero, unsigned index){
    bool Can = true;
    std::vector<unsigned> ressourceNeed = blacksmithInventoryMake[index]->getResource();

    for(unsigned i = 1; i < ressourceNeed.size(); i+=2){
        if(Can && ressourceNeed[i] != 0) {
            std::cout << ressourceNeed[i] << " / " << ressourceNeed[i+1] << std::endl;
            if (!(hero->isItOnEntity(ressourceNeed[i], ressourceNeed[i + 1])))
                Can = false;
        }
        std::cout << Can << std::endl;
    }
    return Can;
}

bool Npc::CanMakePotion(Entity *hero, unsigned index){
    bool Can = true;
    std::vector<unsigned> ressourceNeed = witchInventoryMake[index]->getResource();

    for(unsigned i = 1; i < ressourceNeed.size(); i+=2){
        if(Can && ressourceNeed[i] != 0)
            if(!(hero->isItOnEntity(ressourceNeed[i],ressourceNeed[i+1])))
                Can = false;
    }
    return Can;
}

void Npc::display(Action action) {
    switch (action) {
        case Action::make: {
            std::cout << "Les objets qui peuvent être fabriqués :" << std::endl;
            unsigned i = 0;
            while (i < blacksmithInventoryMake.size()) {
                blacksmithInventoryMake[i]->display();
                i++;
            }
            std::cout << std::endl << std::endl;
            std::cout << "Les objets qui peuvent être améliorés :" << std::endl;
            unsigned j = 0;
            while (j < blacksmithInventoryUpgrade.size()) {
                blacksmithInventoryUpgrade[j]->display();
                j++;
            }
            break;
        }
        case Action::potion: {
            std::cout << "Les potions qui peuvent être achetés :" << std::endl;
            unsigned i = 0;
            while (i < witchInventory.size()) {
                witchInventory[i]->display();
                i++;
            }
            break;
        }
        case Action::loot: {
            std::cout << "Les loods qui peuvent être achetés :" << std::endl;
            unsigned i = 0;
            while (i < traderInventory.size()) {
                traderInventory[i]->display();
                i++;
            }
            break;
        }
        default:
            break;
    }
}

unsigned Npc::returnIndex(const unsigned id, Action action) const{
    unsigned index = 150;
    switch (action){
        case Action::make:
            for(unsigned i = 0; i < blacksmithInventoryMake.size(); i++) {
                if(blacksmithInventoryMake[i]->getId() == id)
                    index = i;
            }
            break;

        case Action::upgrade:

            for(unsigned i = 0; i < blacksmithInventoryUpgrade.size(); i++) {
                if(blacksmithInventoryUpgrade[i]->getId() == id)  index = i;
            }
            break;

        case Action::potion:
            for(unsigned i = 0; i < witchInventory.size(); i++) {
                if(witchInventory[i]->getId() == id)  index = i;
            }
            break;

        case Action::loot:
            for(unsigned i = 0; i < traderInventory.size(); i++) {
                if(traderInventory[i]->getId() == id)  index = i;
            }
            break;

        default:
            break;
    }
    return index;
}
