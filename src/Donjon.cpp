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
    }
    delete Donjon::RoomsMap;
}

void Donjon::generate(){
	
    if(random) seed = time(0);
	srand(seed);

	roomsNb = rand()%(maxRooms-minRooms+1)+minRooms;

	// Initialise la premiere salle au centre du tableau
    unsigned mid = (maxSize - 1)/2;

    if(RoomsMap[mid][mid]->getType() )
    RoomsMap[mid][mid]->setType(roomType::Start);  // Cette ligne pose problème

}

  // Set la seed du donjon
void Donjon::setSeed(unsigned value){
	seed = value;
}

    //Récupère la seed du donjon
unsigned Donjon::getSeed() const{
	return seed;
}

void Donjon::setRandom(bool value){
    random = value;
}
    //Récupère la seed du donjon
bool Donjon::getRandom() const{
    return random;
}

unsigned Donjon::getSize() const{
    return maxSize;
}

Room* Donjon::getRoom(unsigned i, unsigned j) const{
    return RoomsMap[i][j];
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

/* à coder:
void Donjon::roomTypeAffect(){

}*/

std::ostream& operator<<(std::ostream& stream, const Donjon& d)
{
	for (unsigned i = 0; i < d.getSize(); i++)
	{
		for (unsigned j = 0; j < d.getSize(); j++)
		{
			if (d.getRoom(i, j) == nullptr)
			{
				stream << "-";
			}
			else
			{
				switch (d.getRoom(i, j)->getType())
				{
					case roomType::Common:
						stream << "o";
						break;
					
					case roomType::Start:
						stream << "S";
						break;
					
					case roomType::End:
						stream << "X";
						break;
				}
			}
		}
		
		stream << std::endl;
	}
	
	return stream;
}
