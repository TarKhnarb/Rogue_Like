#include "Donjon.h"
#include <iostream>

int main(){
	
	Donjon d;
	
	d.generate();
	std::cout << d;
	std::cout << "seed: " << d.getSeed() << std::endl;
	
	return 0;
}
