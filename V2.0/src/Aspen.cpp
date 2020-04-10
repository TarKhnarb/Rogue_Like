#include <iostream>
#include <istream>

#include "Donjon.h"

int main(){

    unsigned stage = 2;

    Donjon test(stage);
    std::cout << test.getStage();

	return 0;
}
