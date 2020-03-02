#include "Donjon.h"
#include <iostream>

int main(){

    Donjon test;

    test.generate();

    std::cout << test.getSeed() << std::endl;


    return 0;
}
