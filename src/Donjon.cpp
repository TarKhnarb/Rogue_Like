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
    for(unsigned i = 0; i < maxSize; i++) {
        for (unsigned j = 0; j < maxSize; j++) {
            delete RoomsMap[i][j];
            RoomsMap[i][j] = nullptr;
        }
    }
}

void Donjon::generate(){
	
    if(random) seed = time(0);
	srand(seed);

	roomsNb = rand()%(maxRooms-minRooms+1)+minRooms;

    unsigned mid = (maxSize - 1)/2;
	
	unsigned roomsCnt = 0; // Compteur de salles posées
	unsigned density = 2; // >= 2, traduit la densité des cases (plus elle est élévée, plus on s'assure de poser assez de salles)
	
	while (roomsNb != roomsCnt) {

	    reset(); // Reset (nettoie le tableau et genere le depart au milieu du tableau)
	    roomsCnt = 0;
		
        for (unsigned k = 1; k <= mid; k++) // chaque 'cercle' autour du point central
        {
            for (unsigned i = mid-k+1; i <= mid+k; i++) // première ligne, en haut à l'horizontal, sauf case tout en haut à gauche
            {
                if ((i > 0 && RoomsMap[i-1][mid-k]) || RoomsMap[i][mid-k+1]) // test sur les cases à gauche et en dessous
                {
                    if (roomsCnt < roomsNb && rand()%density) // place une salle seulement si le mod est différent de 0
                    {
                        RoomsMap[i][mid-k] = new Room();
                        roomsCnt ++;
                    }
                }
            }

            if (RoomsMap[mid-k+1][mid-k]) // case tout en haut à gauche
            {
                if(roomsCnt < roomsNb && rand()%density)
                {
                    RoomsMap[mid-k][mid-k] = new Room();
                    roomsCnt ++;
                }
            }

            for (unsigned j = mid-k+1; j <= mid+k-1; j++) // deuxième ligne, à droite à la verticale
            {
                if ((j > 0 && RoomsMap[mid+k][j-1]) || RoomsMap[mid+k-1][j]) // test sur les cases au dessus et à gauche
                {
                    if (roomsCnt < roomsNb && rand()%density)
                    {
                        RoomsMap[mid+k][j] = new Room();
                        roomsCnt ++;
                    }
                }
            }

            for (unsigned j = mid-k+1; j <= mid+k-1; j++) // troisième ligne, à gauche à la verticale
            {
                if ((j > 0 && RoomsMap[mid-k][j-1]) || RoomsMap[mid-k+1][j]) // test sur les cases au dessus et à droite
                {
                    if (roomsCnt < roomsNb && rand()%density)
                    {
                        RoomsMap[mid-k][j] = new Room();
                        roomsCnt ++;
                    }
                }
            }

            for (unsigned i = mid-k; i <= mid+k; i++) // dernière ligne, en bas à l'horizontal
            {
                if ((i+1 < maxSize && RoomsMap[i+1][mid+k]) || RoomsMap[i][mid+k-1]) // test de la case à gauche et au dessus
                {
                    if (roomsCnt < roomsNb && rand()%density)
                    {
                        RoomsMap[i][mid+k] = new Room();
                        roomsCnt ++;
                    }
                }
            }
        }
	}
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
            if (RoomsMap[i][j])
            {
                if (RoomsMap[i+1]){ // Est (1)
                    RoomsMap[i][j]->placeDoor(1);
                }

                if (RoomsMap[i-1][j]){ // West (3)
                    RoomsMap[i][j]->placeDoor(3);
                }

                if (RoomsMap[i][j+1]){ // Sud (2)
                    RoomsMap[i][j]->placeDoor(2);
                }

                if (RoomsMap[i][j-1]){ // Nord (0)
                    RoomsMap[i][j]->placeDoor(0);
                }
            }
        }
     }
}

/* à coder:
void Donjon::roomTypeAffect(){

}*/

void Donjon::reset() {
    for(unsigned i = 0; i < maxSize; i++) {
        for (unsigned j = 0; j < maxSize; j++) {
            delete RoomsMap[i][j];
            RoomsMap[i][j] = nullptr;
        }
    }

    unsigned mid = (maxSize - 1)/2;
    RoomsMap[mid][mid] = new Room(Start);
}

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
