#include "Donjon.h"

Donjon::Donjon(unsigned stageNumb, Entity* aspen):
        hero(aspen),
        stageNb(stageNumb),
        stage(0),
        currentStage(new Stage(hero)){

    currentStage->generate(stage);
    currentStage->affectRoomTypeMonsterObject();

    std::cout << currentStage;
}

Donjon::~Donjon(){
	if (currentStage){
        delete currentStage;
        currentStage = nullptr;
	}
}


Stage* Donjon::getCurrentStage() const {
    return currentStage;
}

Room* Donjon::getRoom(unsigned i, unsigned j){
    return currentStage->getRoom(i, j);
}

unsigned Donjon::getStage() {
    return stage;
}

void Donjon::nextStage() {
    if(stage < stageNumber){
        ++stage;
        delete currentStage;
        currentStage = new Stage(hero);
        currentStage->generate(stage);
        currentStage->affectRoomTypeMonsterObject();

        std::cout << currentStage;
    }
    else
        throw std::runtime_error ("Donjon::nextStage(" + std::to_string(stage) + ") - Bravo ! Vous êtes arrivé à bout de ce donjon !");

}

void Donjon::displayDoors(unsigned i, unsigned j) {

    std::vector<Door*> door = currentStage->getDoors(i, j);

    std::cout << "(0): North, (1): East, (2): South, (3): West" << std::endl;
    std::cout << std::endl;

    for(unsigned k = 0; k < door.size(); ++k){

        if(door[k]){
            std::cout << "Door n° " << k << " :" << std::endl;
            std::cout << "  Open ? : " << door[k]->getOpen() << std::endl;
        }
        std::cout << std::endl;
    }
}

void Donjon::displayMonsters(unsigned i, unsigned j) {

    std::vector<Entity*> monst = currentStage->getMonsters(i, j);
    std::cout << "Nb monstres = " << monst.size() << std::endl;
    std::cout << std::endl;

    for(unsigned k = 0; k < monst.size(); ++k){

        if(monst[k]){
            std::cout << "Monster n° " << k << " :" << std::endl;
            std::cout << "  Name : " << monst[k]->getName() << std::endl;
            std::cout << "  Position X/Y : " << monst[k]->getPosition(true) << " / " << monst[k]->getPosition(false) << std::endl;
        }
        std::cout << std::endl;
    }
}

void Donjon::displayRocks(unsigned i, unsigned j) {

    const std::vector<Rock> rocks = currentStage->getRocks(i, j);

    if(rocks.size() > 0){
        std::cout << "Nb rochers = " << rocks.size() << std::endl;
        std::cout << std::endl;

        for(unsigned k = 0; k < rocks.size(); ++k){

            std::cout << "Rock n° " << k << " :" << std::endl;
            std::cout << "  Position X/Y : " << rocks[k].getPosition(true) << " / " << rocks[k].getPosition(false) << std::endl;
            std::cout << std::endl;
        }
    }
    else
        std::cout << "Aucun rocher" << std::endl;
}

void Donjon::displayChest(unsigned i, unsigned j) {

    Chest * ches = currentStage->getChest(i, j);

    if(ches){
        std::cout << " Chest :" << std::endl;
        ches->display();

        std::cout << std::endl;
    }
    else
        std::cout << "Aucun coffre" << std::endl;
}
