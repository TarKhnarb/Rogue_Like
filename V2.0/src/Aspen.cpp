#include <iostream>
#include <istream>

#include "Base.h"
#include "Entity.h"

int main(){

    std::cout << "0" << std::endl;

    Entity Aspen;
    std::cout << "1" << std::endl;
    Aspen = Entity(0, 0); // Aspen en 0,0
    std::cout << "2" << std::endl;
    Aspen.addInventoryObject(4);
    std::cout << "3" << std::endl;
    Base test(Aspen, 2); // Base de lvl 1
    std::cout << "4" << std::endl;
    test.storeInChest(0, 0);

    std::cout << "5" << std::endl;

    test.display();

    std::cout << "6" << std::endl;

	return 0;
}
