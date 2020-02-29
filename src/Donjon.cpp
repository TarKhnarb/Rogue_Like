#include "Donjon.h"

#include <cstdlib>
#include <ctime>

      //------------//
     //Constructeur//
    //------------//
Donjon::Donjon(){
    
    for(int unsigned i = 0; i < maxSize; i++)
    {
        for(int unsigned j = 0; j < maxSize; j++)
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
    for(int unsigned i = 0; i < maxSize; i++)
    {
        for(int unsigned j = 0; j < maxSize; j++)
        {
            RoomsMap[i][j] = nullptr;
            delete [] Donjon::RoomsMap;
        }
    }
}

void Donjon::generate(){
    
    if(random) seed = time(0);
	srand(seed);

	roomsNb = rand()%(maxRooms-minRooms+1)+minRooms;

	// Initialise la premiere salle au centre du tableau
    unsigned mid = (maxSize - 1)/2;
    RoomsMap[mid][mid]->setType(Room::roomType::Start);

    // Maintenant c'est la merde

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

// à coder:
void Donjon::countDoors(){

    for(int unsigned i = 0; i < maxSize; i++){
        for(int unsigned j = 0; j < maxSize; j ++){
            int var = RoomsMap[i][j]->getDoorsNb();
            if(RoomsMap[i][j]->getType() != Room::roomType::Common)
            {
                if(RoomsMap[i+1][j]->getType() != Room::roomType::Common){ // Est (1)
                    RoomsMap[i][j]->setDoorsNb(var++);
                    RoomsMap[i][j]->setDoorExist(1, true);
                }
                if(RoomsMap[i-1][j]->getType() != Room::roomType::Common){ // West (3)
                    RoomsMap[i][j]->setDoorsNb(var++);
                    RoomsMap[i][j]->setDoorExist(3, true);
                }
                if(RoomsMap[i][j+1]->getType() != Room::roomType::Common){ // Sud (2)
                    RoomsMap[i][j]->setDoorsNb(var++);
                    RoomsMap[i][j]->setDoorExist(2, true);
                }
                if(RoomsMap[i][j-1]->getType() != Room::roomType::Common) { // Nord (0)
                    RoomsMap[i][j]->setDoorsNb(var++);
                    RoomsMap[i][j]->setDoorExist(0, true);
                }
            }
        }
    }
}
void Donjon::doorTypeAffect(int){

}
