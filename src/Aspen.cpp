#include "Donjon.h"
#include <iostream>

int main(){

	
	Stage d;
	
	d.generate();
	d.roomTypeMonsterObjectAffect();
	std::cout << d.getSeed() << std::endl;
	std::cout << d;
	d.getType();

	//std::cout << d.getStage() << std::endl;

	return 0;
}
