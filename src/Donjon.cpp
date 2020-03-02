#include "Donjon.h"

#include <cstdlib>
#include <ctime>

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

    // Maintenant c'est la merde
    std::cout << "Généré !! " << seed << std::endl;
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

            switch (RoomsMap[i][j]->getType()){

                case roomType::None:
                    break;
                default:

                    switch (RoomsMap[i+1][j]->getType()){ // Est (1)
                        case roomType::None:
                            break;
                        default:
                            RoomsMap[i][j]->placeDoor(1);
                            break;
                    }

                    switch (RoomsMap[i-1][j]->getType()){ // West (3)
                        case roomType::None:
                            break;
                        default:
                            RoomsMap[i][j]->placeDoor(3);
                    }

                    switch (RoomsMap[i][j+1]->getType()){ // Sud (2)
                        case roomType::None:
                            break;
                        default:
                            RoomsMap[i][j]->placeDoor(2);
                    }

                    switch (RoomsMap[i][j-1]->getType()){ // Nord (0)
                        case roomType::None:
                            break;
                        default:
                            RoomsMap[i][j]->placeDoor(0);


                    }
            }
        }
     }
}

// à coder:
void Donjon::roomTypeAffect(){

}