#include "Donjon.h"
#include <iostream>

int main(){

	
	Donjon d;
	
	d.generate();
	std::cout << d.getSeed() << std::endl;
	std::cout << d;

	//std::cout << d.getStage() << std::endl;

	return 0;
}
