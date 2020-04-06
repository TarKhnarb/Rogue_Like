#include <iostream>
#include <istream>

#include "Base.h"
#include "Entity.h"

int main(){

    Entity Aspen;
    Aspen = Entity(0, 0); // Aspen en 0,0
    Aspen.addInventoryObject(4);
    Base test;
    test = Base(Aspen, 2); // Base de lvl 1 (il faut penser à mettre des chest != nullptr dans le constructeur, en fonction du level
    test.storeInChest(0, 0); // WARNING l'erreur de segmentation était ici
    test.display();
	return 0;
}
