#include "Donjon.h"
#include <iostream>

int main(){

	
	Donjon d;
	/* SUPPRIMER CE COMMENTAIRE POUR CHOISIR D'ENTRER LE SEED AVANT DE GÉNÉRER L'ÉTAGE
	std::cout << "random: ";
	bool random;
	std::cin >> random;
	d.setRandom(random);
	
	if (!random) // un peu redondant, voir s'il ne faut pas modifier setSeed ou setRandom
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
	//std::cout << d.getStage() << std::endl;
	
	return 0;
}
