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
            delete [] RoomsMap;
        }
    }
}

      //-------------//
     //Genere_donjon//
    //-------------//
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

// à coder:
void Donjon::countDoors(){
    for(int unsigned i = 0; i < maxSize; i++){
        for(int unsigned j = 0; j < maxSize; j ++){
            if(RoomsMap[i][j].getType() != 0)
            {
                if(RoomsMap[i+1][j]->getType() == 0) setDoorsNb(1); // VERRIFIER SI ++ FOCTIONNE SINON CRÉER UNE AUTRE FONCTION AVECSET ET GET DE NBDOOR
                if(RoomsMap[i-1][j]->getType() == 0) setDoorsNb(1);
                if(RoomsMap[i][j+1]->getType() == 0) setDoorsNb(1);
                if(RoomsMap[i][j-1]->getType() == 0) setDoorsNb(1);
            }
        }
    }
}
void Donjon::doorTypeAffect(int){

}
