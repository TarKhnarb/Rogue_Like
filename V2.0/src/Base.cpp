#include "Base.h"

Base::Base(Entity & aspen, unsigned lvl):
        hero(aspen),
        chests (lvl, nullptr){

    std::cout << "je suis passé" << std::endl;
    for (unsigned i = 0; i < lvl; i++){
        chests[i] = new Chest(hero, Chest::orientation::South);
    }
    std::cout << "Là aussi !" << std::endl;
}

Base::~Base() {
    saveChests();
    for(auto chest : chests){
        if(chest){
            delete chest;
        }
    }
}

void Base::upgradeBase(){
    if(lvl <= maxBaseLvl){
        lvl++;
        chests.push_back(new Chest(hero, Chest::orientation::South));
    }
}

void Base::storeInChest(unsigned chestId, unsigned indexI) {
	if(chests[chestId]){
		chests[chestId]->placeInChest(indexI);
	}
	else{
		std::cout << "Base::storeInChest : " << chestId << " n'est pas un id convenable" << std::endl;
	}
}

void Base::removeFromChest(unsigned chestId, unsigned indexC) { // gère automatiquement en fonction de la place disponible dans l'inventaire du joueur le nb d'objects retirés

    if(chests[chestId]){
        chests[chestId]->removeFromChest(indexC);
    }
    else{
        std::cout << "Base::removeFromChest : " << chestId << " n'est pas un id convenable" << std::endl;
    }
}

void Base::saveChests() {
    for(unsigned i = 0; i < maxBaseLvl; i++){
        if(chests[i]){ // Si le coffre existe on ecrit dans un fichier les id des objets et leur nb (Si on a rien on saute une ligne)
            chests[i]->saveChest("data/Base_Save/chest"+std::to_string(i)+".csv");
        }
    }
}

void Base::loadChests() {
    for(unsigned i = 0; i < lvl; i++){
        chests[i]->loadChest("data/Base_Save/chest"+std::to_string(i)+".csv");
    }
}

void Base::display() {
    for(auto chest : chests){
        if(chest){
            std::cout << "Chests :" << std::endl;
            std::cout << "      ";
            chest->display();
            std::cout << std::endl;
        }
    }
}