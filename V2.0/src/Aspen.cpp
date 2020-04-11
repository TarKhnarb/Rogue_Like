#include <iostream>
#include <istream>

#include "Donjon.h"
#include "Entity.h"

int main(){

    unsigned stage = 2;

    float x = 0.0, y = 0.0;

    Entity Aspen(x, y);

    Donjon test(stage, Aspen);
    std::cout << test.getStage();

	return 0;
}
