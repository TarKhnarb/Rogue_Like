#include "Donjon.h"
#include <iostream>

int main(){
	
	Donjon d;
	/*
	std::cout << "random: ";
	bool random;
	std::cin >> random;
	d.setRandom(random);
	
	if (!random)
	{
		std::cout << "seed: ";
		unsigned seed;
		std::cin >> seed;
		d.setSeed(seed);
	}
	*/
	d.generate();
	
	std::cout << d;
	std::cout << "seed: " << d.getSeed() << std::endl;
	std::cout << d.getStage() << std::endl;
	
	return 0;
}
