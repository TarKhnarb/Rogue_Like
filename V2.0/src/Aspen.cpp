#include <iostream>
#include <istream>

#include "Base.h"
#include "Entity.h"

int main(){

    std::cout << "0";

    Entity Aspen;
    Aspen = Entity(0, 0); // Aspen en 0,0
    std::cout << "1";
    Aspen.addInventoryObject(4);
    std::cout << "2";
    Base test;
    test = Base(Aspen, 2); // Base de lvl 1
    std::cout << "3";
    test.storeInChest(0, 0);

    test.display();

	return 0;
}
