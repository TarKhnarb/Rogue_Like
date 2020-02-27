#include "Donjon.h"
#include "Salle.cpp"

#include <cstdlib>
#include <ctime>

     //-------------//
     //Constructeur//
    //------------//
Donjon::Donjon(){
    
    for(int i = 0; i < maxSize; i++)
    {
        for(int j = 0; j < maxSize; j++)
        {
            RoomsMap[i][j] = new Room();
        }
    }
	
	seed = 1;
    random = true;
}

      //-----------//
     //Destructeur//
    //-----------//
Donjon::~Donjon(){
    for(int i = 0; i < maxSize; i++)
    {
        for(int j = 0; j < maxSize; j++)
        {
            RoomsMap[i][j] = nullptr;
        }
    }

    delete[] RoomsMap;
}

  // Set la seed du donjon
void Donjon::setSeed(int value){
	seed = abs(value);
}

    //Récupère la seed du donjon
int Donjon::getSeed(){
	return seed;
}

void Donjon::setRandom(bool value){
    random = value;
}
    //Récupère la seed du donjon
bool Donjon::getRandom(){
    return random;
}

      //-------------//
     //Genere_donjon//
    //-------------//
void Donjon::generate(){
    
    for(int i = 0; i < Gmax; i++)
	{
		for(int j = 0; j < Gmax; j++)
		{
			RoomsMap[i][j] = 0;
		}
	}
    
    if(Random::random) seed = time(0);
	srand(seed);

	nbRoom = rand()%(Smax-Smin+1)+Smin;

	// Initialise la premiere salle au centre du tableau
    RoomsMap[10][10] = Room::setTypeRoom();

}
