#include "Donjon.h"
#include <iostream>

int main(){

/*    Donjon test;

    test.generate();

    std::cout << test;*/

    Room test;

    std::cout << "créer une piece" << std::endl;

    test.setType(roomType::Start);

    std::cout << "affecte un type de piece"  << std::endl;

    std::cout << test.getType() << std::endl;

    std::cout << "test ?" << std::endl;

    return 0;
}
