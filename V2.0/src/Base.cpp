#include "Base.h"

Base::Base(Entity & aspen, unsigned lvl):
        hero(aspen),
        chests (lvl, nullptr){}

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
    chests[chestId]->removeFromChest(indexC);
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
