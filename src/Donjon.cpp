#include "Donjon.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

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
    stage = 0;
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
    stage = 0;
}

void Donjon::generate(){
	
    if(random) seed = time(0);
	srand(seed);

	roomsNb = rand()%(maxRooms-minRooms+1)+minRooms;

    unsigned mid = (maxSize - 1)/2;
	
	unsigned roomsCnt = 0; // Compteur de salles posées
	unsigned density = 2; // >= 2, Traduit la densité des cases (plus elle est élévée, plus on s'assure de poser assez de salles)
	
	while (roomsNb != roomsCnt) { // Génère les salles autour de la salle de départ (centre)

	    reset(); // Reset (nettoie le tableau et genere le depart au milieu du tableau)
        roomsCnt = 0; // Au cas où on recommence

            // Génère les salles du donjon
        for (unsigned k = 1; k <= mid; k++) // Chaque 'cercles' autour du point central
        {
            for (unsigned i = mid-k+1; i <= mid+k; i++) // Première ligne, en haut à l'horizontal, sauf case tout en haut à gauche (car rien encore à côté)
            {
                if ((i > 0 && RoomsMap[i-1][mid-k]) || RoomsMap[i][mid-k+1]) // Test sur les cases à gauche et en dessous
                {
                    if (roomsCnt < roomsNb-1 && rand()%density) // Place une salle seulement si le mod est différent de 0
                    {
                        RoomsMap[i][mid-k] = new Room();
                        roomsCnt ++;
                    }
                }
            }

            if (RoomsMap[mid-k+1][mid-k]){ // Traitement de la case tout en haut à gauche

                if(roomsCnt < roomsNb-1 && rand()%density)
                {
                    RoomsMap[mid-k][mid-k] = new Room();
                    roomsCnt ++;
                }
            }

            for (unsigned j = mid-k+1; j <= mid+k-1; j++) // Deuxième ligne, à droite à la verticale
            {
                if ((j > 0 && RoomsMap[mid+k][j-1]) || RoomsMap[mid+k-1][j]) // Test sur les cases au dessus et à gauche
                {
                    if (roomsCnt < roomsNb-1 && rand()%density)
                    {
                        RoomsMap[mid+k][j] = new Room();
                        roomsCnt ++;
                    }
                }
            }

            for (unsigned j = mid-k+1; j <= mid+k-1; j++) // Troisième ligne, à gauche à la verticale
            {
                if ((j > 0 && RoomsMap[mid-k][j-1]) || RoomsMap[mid-k+1][j]) // test sur les cases au dessus et à droite
                {
                    if (roomsCnt < roomsNb-1 && rand()%density)
                    {
                        RoomsMap[mid-k][j] = new Room();
                        roomsCnt ++;
                    }
                }
            }

            for (unsigned i = mid-k; i <= mid+k; i++) // Dernière ligne, en bas à l'horizontal
            {
                if ((i+1 < maxSize && RoomsMap[i+1][mid+k]) || RoomsMap[i][mid+k-1]) // Test de la case à gauche et au dessus
                {
                    if (roomsCnt < roomsNb-1 && rand()%density)
                    {
                        RoomsMap[i][mid+k] = new Room();
                        roomsCnt ++;
                    }
                }
            }

            if(roomsCnt == roomsNb-1){ // Place la dernière salle pour le Boss le plus à l'extérieur

                for (unsigned i = mid-k+1; i <= mid+k; i++) // Première ligne, en haut à l'horizontal, sauf case tout en haut à gauche (car rien encore à côté)
                {       // Test si la case même n'est pas deja une salle, compte si elle peut se raccrocher au donjon et ve
                    if (!RoomsMap[i][mid-k] && countRoomsAround(i, mid-k))//(i > 0 && RoomsMap[i-1][mid-k]) xor bool(RoomsMap[i][mid-k+1]) xor (i+1 < maxSize && RoomsMap[i+1][mid-k])) // Test sur les cases à gauche et en dessous et a droite
                    {
                        if (roomsCnt == roomsNb-1 && rand()%density) // Place une salle seulement si le mod est différent de 0
                        {
                            RoomsMap[i][mid-k] = new Room(Boss);
                            roomsCnt ++;
                        }
                    }
                }

                if (!RoomsMap[mid-k][mid-k] && countRoomsAround(mid-k, mid-k)){ // Traitement de la case tout en haut à gauche
                    if(roomsCnt == roomsNb-1 && rand()%density)
                    {
                        RoomsMap[mid-k][mid-k] = new Room(Boss);
                        roomsCnt ++;
                    }
                }

                for (unsigned j = mid-k+1; j <= mid+k-1; j++) // Deuxième ligne, à droite à la verticale
                {
                    if (!RoomsMap[mid+k][j] && countRoomsAround(mid+k, j)) //((j > 0 && RoomsMap[mid+k][j-1]) xor bool(RoomsMap[mid+k-1][j]) xor (j+1 < maxSize && RoomsMap[mid+k][j+1])) // Test sur les cases au dessus et à gauche et à droite
                    {
                        if (roomsCnt == roomsNb-1 && rand()%density)
                        {
                            RoomsMap[mid+k][j] = new Room(Boss);
                            roomsCnt ++;
                        }
                    }
                }

                for (unsigned j = mid-k+1; j <= mid+k-1; j++) // Troisième ligne, à gauche à la verticale
                {
                    if (!RoomsMap[mid-k][j] && countRoomsAround(mid-k, j)) //(j > 0 && RoomsMap[mid-k][j-1]) xor bool(RoomsMap[mid-k+1][j]) xor (j+1 < maxSize && RoomsMap[mid-k][j+1])) // test sur les cases au dessus en dessous et à droite
                    {
                        if (roomsCnt == roomsNb-1 && rand()%density)
                        {
                            RoomsMap[mid-k][j] = new Room(Boss);
                            roomsCnt ++;
                        }
                    }
                }

                for (unsigned i = mid-k; i <= mid+k; i++) // Dernière ligne, en bas à l'horizontal
                {
                    if (!RoomsMap[i][mid+k] && countRoomsAround(i, mid+k))//(i+1 < maxSize && RoomsMap[i+1][mid+k]) xor bool(RoomsMap[i][mid+k-1]) xor (i > 0 && RoomsMap[i-1][mid+k])) // Test de la case à droite au dessus et à gauche
                    {
                        if (roomsCnt == roomsNb-1 && rand()%density)
                        {
                            RoomsMap[i][mid+k] = new Room(Boss);
                            roomsCnt ++;
                        }
                    }
                }

            }
        }
	}
    stage++;
    std::cout << "roomsNb = " << roomsNb << std::endl;
    std::cout << "roomsCnt = " << roomsCnt << std::endl;
    std::cout << "seed = " << seed << std::endl;
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

unsigned Donjon::getStage() const {
    return stage;
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
    if (stage == 0) {
        RoomsMap[mid][mid] = new Room(Start);
    }
    else RoomsMap[mid][mid] = new Room(CommonStart);
}

bool Donjon::countRoomsAround(unsigned i, unsigned j) { // prends les coords d'une case et retourne le nb de salles EXISTENTE autour

    unsigned count = 0;

    if(i > 0){
        if (RoomsMap[i-1][j]) { // Case au dessus
            count++;
        }
    }

    if(j > 0){
        if (RoomsMap[i][j-1]) { // Case à gauche
            count++;
        }
    }

    if(i < maxSize){
       if(RoomsMap[i+1][j]){ // Case en dessous
           count++;
       }
    }

    if(j < maxSize){
        if(RoomsMap[i][j+1]){ // Case à droite
            count++;
        }
    }

    return count == 1; //
}

std::ostream& operator<<(std::ostream& stream, const Donjon& d){

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
					
					case roomType::Boss:
						stream << "X";
						break;

				    case roomType::CommonStart:
				        stream << "s";
                        break;
				}
			}
		}
		
		stream << std::endl;
	}
	
	return stream;
}
