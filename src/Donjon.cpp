#include "Donjon.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

      //------------//
     //Constructeur//
    //------------//
Donjon::Donjon(){
    
    for(unsigned i = 0; i < maxSize; i++)
    {
        for(unsigned j = 0; j < maxSize; j++)
        {
            RoomsMap[i][j] = nullptr;
        }
    }
	
	seed = 1;
    random = true;
}

      //-----------//
     //Destructeur//
    //-----------//
Donjon::~Donjon(){
    for(unsigned i = 0; i < maxSize; i++)
    {
        for(unsigned j = 0; j < maxSize; j++)
        {
            RoomsMap[i][j] = nullptr;
        }
        delete [] Donjon::RoomsMap;
    }
}

void Donjon::generate(){
    
    if(random) seed = time(0);
	srand(seed);

	roomsNb = rand()%(maxRooms-minRooms+1)+minRooms;

	// Initialise la premiere salle au centre du tableau
    unsigned mid = (maxSize - 1)/2;

    RoomsMap[mid][mid]->setType(roomType::Start);


}

  // Set la seed du donjon
void Donjon::setSeed(unsigned value){
	seed = value;
}

    //Récupère la seed du donjon
unsigned Donjon::getSeed(){
	return seed;
}

void Donjon::setRandom(bool value){
    random = value;
}
    //Récupère la seed du donjon
bool Donjon::getRandom(){
    return random;
}

void Donjon::placeDoors(){

    for(unsigned i = 0; i < maxSize; i++){
        for(unsigned j = 0; j < maxSize; j ++){
            if (RoomsMap[i][j] != nullptr)
            {
                if (RoomsMap[i+1] != nullptr){ // Est (1)
                    RoomsMap[i][j]->placeDoor(1);
                }

                if (RoomsMap[i-1][j] != nullptr){ // West (3)
                    RoomsMap[i][j]->placeDoor(3);
                }

                if (RoomsMap[i][j+1] != nullptr){ // Sud (2)
                    RoomsMap[i][j]->placeDoor(2);
                }

                if (RoomsMap[i][j-1] != nullptr){ // Nord (0)
                    RoomsMap[i][j]->placeDoor(0);
                }
            }
        }
     }
}

// à coder:
void Donjon::roomTypeAffect(){

}
