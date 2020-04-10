#include <iostream>
#include <istream>

#include "Donjon.h"
#include "Entity.h"

int main(){

    unsigned stage = 2;

    Entity Aspen(0,0);

    Donjon test(stage, Aspen);
    std::cout << test.getStage();

	return 0;
}
