#include "Donjon.h"
#include <iostream>

int main(){
	
	Donjon d;
	
	d.generate();
	std::cout << d;

	std::cout << d.getStage() << std::endl;

	return 0;
}
