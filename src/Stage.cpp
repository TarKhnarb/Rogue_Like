#include "Stage.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

/****************
 * Constructeur *
 ***************/

Stage::Stage(){
    
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

/**************
 * Destructor *
 *************/

Stage::~Stage(){
    for(unsigned i = 0; i < maxSize; i++)
	{
        for (unsigned j = 0; j < maxSize; j++)
		{
            delete RoomsMap[i][j];
            RoomsMap[i][j] = nullptr;
        }
    }
}

/************
 * Generate *
 ***********/

void Stage::generate(){
	
    if(random) seed = time(0);
	srand(seed);

	roomsNb = rand()%(maxRooms-minRooms+1)+minRooms;

    unsigned mid = (maxSize - 1)/2;
	
	unsigned roomsCnt = 0; // Compteur de salles posées
	unsigned density = 2; // >= 2, traduit la densité des cases (plus elle est élévée, plus on s'assure de poser assez de salles)
	
	while (roomsNb != roomsCnt){ // Génère les salles autour de la salle de départ (centre)

	    reset(); // Reset (nettoie le tableau et genere le depart au milieu du tableau)
        roomsCnt = 0; // Au cas où on recommence

		// Génère les salles du Stage
        for (unsigned k = 1; k <= mid; k++) // Chaque 'cercles' autour du point central
        {
            for (unsigned i = mid-k+1; i <= mid+k; i++) // Première ligne, en haut à l'horizontal, sauf case tout en haut à gauche (car rien encore à côté)
            {
                if ((i > 0 && RoomsMap[i-1][mid-k]) || RoomsMap[i][mid-k+1]) // Test sur les cases à gauche et en dessous
                {
                    if (roomsCnt < roomsNb-1 && rand()%density) // Place une salle seulement si le mod est différent de 0
					// on écrit roomsNb-1 car on garde une salle pour le boss
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
			
			/*
			 * La salle du boss
			 */
			
            if(roomsCnt == roomsNb-1){

                for (unsigned i = mid-k+1; i <= mid+k; i++) // Première ligne, en haut à l'horizontal, sauf case tout en haut à gauche
                {       // Test si la case même n'est pas deja une salle, compte si elle peut se raccrocher au Stage et ve
                    if (!RoomsMap[i][mid-k] && countRoomsAround(i, mid-k) == 1)
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
                    if (!RoomsMap[mid+k][j] && countRoomsAround(mid+k, j))
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
                    if (!RoomsMap[mid-k][j] && countRoomsAround(mid-k, j))
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
                    if (!RoomsMap[i][mid+k] && countRoomsAround(i, mid+k))
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

/************
 * Set Seed *
 ***********/

void Stage::setSeed(unsigned value){
	seed = value;
}

/************
 * Get Seed *
 ***********/

unsigned Stage::getSeed() const{
	return seed;
}

/**************
 * Set Random *
 *************/

void Stage::setRandom(bool value){
    random = value;
}

/**************
 * Get Random *
 *************/

bool Stage::getRandom() const{
    return random;
}

/************
 * Get Size *
 ***********/

unsigned Stage::getSize() const{
    return maxSize;
}

/*************
 * Get Stage *
 ************/

unsigned Stage::getStage() const {
    return stage;
}

/************
 * Get Room *
 ***********/

Room* Stage::getRoom(unsigned i, unsigned j) const{
    return RoomsMap[i][j];
}

/***************
 * Place Doors *
 **************/

void Stage::placeDoors(){

    for(unsigned i = 0; i < maxSize; i++){
        for(unsigned j = 0; j < maxSize; j ++){
            if(RoomsMap[i][j]){
                if (i > 0 && RoomsMap[i-1][j]) { // Left Room
                    RoomsMap[i][j]->placeDoor(3);
                }


                if (j > 0 && RoomsMap[i][j-1]) { // Room above
                    RoomsMap[i][j]->placeDoor(0);
                }

                if(i+1 < maxSize && RoomsMap[i+1][j]){ // Right Room
                    RoomsMap[i][j]->placeDoor(1);
                }

                if(j+1 < maxSize && RoomsMap[i][j+1]){ // Room below
                    RoomsMap[i][j]->placeDoor(2);
                }
            }
        }
     }
}


void Stage::roomTypeMonsterObjectAffect(){

    for(unsigned i = 0; i < maxSize; i++){
        for(unsigned j = 0; j < maxSize; j++){
            if(RoomsMap[i][j] && RoomsMap[i][j]->getType() == roomType::Common){
                
                switch (RoomsMap[i][j]->getDoorsNb()){
                    case 1:
                        if(RoomsMap[i][j]->getDoor(0)){ // Doors at North
                            RoomsMap[i][j]->setType(Room1N);
                        }

                        if(RoomsMap[i][j]->getDoor(1)){ // Doors at East
                            RoomsMap[i][j]->setType(Room1E);
                        }

                        if(RoomsMap[i][j]->getDoor(2)){ // Doors at South
                            RoomsMap[i][j]->setType(Room1S);
                        }

                        if(RoomsMap[i][j]->getDoor(3)){ // Doors at West
                            RoomsMap[i][j]->setType(Room1W);
                        }
                        break;

                    case 2:
                        if(RoomsMap[i][j]->getDoor(0) && RoomsMap[i][j]->getDoor(2)){ // Doors at North South
                            if(seed % 2){
                                RoomsMap[i][j]->setType(Room2NS1);
                            }
                            else{
                                RoomsMap[i][j]->setType(Room2NS2);
                            }
                        }

                        if(RoomsMap[i][j]->getDoor(0) && RoomsMap[i][j]->getDoor(2)){ // Doors at West East 1
                            if(seed % 2){
                                RoomsMap[i][j]->setType(Room2WE1);
                            }
                            else{
                                RoomsMap[i][j]->setType(Room2WE2);
                            }
                        }

                        if(RoomsMap[i][j]->getDoor(0) && RoomsMap[i][j]->getDoor(1)){ // Doors at North East
                            RoomsMap[i][j]->setType(Room4NESW);
                        }

                        if(RoomsMap[i][j]->getDoor(0) && RoomsMap[i][j]->getDoor(3)){ // Doors at North West
                            RoomsMap[i][j]->setType(Room4NESW);
                        }

                        if(RoomsMap[i][j]->getDoor(1) && RoomsMap[i][j]->getDoor(2)){ // Doors at South East
                            RoomsMap[i][j]->setType(Room4NESW);
                        }

                        if(RoomsMap[i][j]->getDoor(2) && RoomsMap[i][j]->getDoor(3)){ // Doors at South West
                            RoomsMap[i][j]->setType(Room4NESW);
                        }
                        break;

                    case 3:
                        if(RoomsMap[i][j]->getDoor(0) && RoomsMap[i][j]->getDoor(1) && RoomsMap[i][j]->getDoor(2)){ // Doors at North, East, South
                            RoomsMap[i][j]->setType(Room3NES);
                        }

                        if(RoomsMap[i][j]->getDoor(1) && RoomsMap[i][j]->getDoor(2) && RoomsMap[i][j]->getDoor(3)){ // Doors at East, South, West
                            RoomsMap[i][j]->setType(Room3ESW);
                        }

                        if(RoomsMap[i][j]->getDoor(0) && RoomsMap[i][j]->getDoor(2) && RoomsMap[i][j]->getDoor(3)){ // Doors at North, South, West
                            RoomsMap[i][j]->setType(Room3NSW);
                        }

                        if(RoomsMap[i][j]->getDoor(0) && RoomsMap[i][j]->getDoor(1) && RoomsMap[i][j]->getDoor(3)){ // Doors at North, East, West
                            RoomsMap[i][j]->setType(Room3NEW);
                        }
                        break;
                    case 4:
                        RoomsMap[i][j]->setType(Room4NESW);
                        break;
                }
            }
        }
    }
}

/*********
 * Reset *
 ********/

void Stage::reset() {

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

/************************
 * Count Room's Arround *
 ***********************/

bool Stage::countRoomsAround(unsigned i, unsigned j) { // prend les coords d'une case et retourne le nb de salles EXISTANTES autour
    
    unsigned count = 0;

    if(i > 0){
        if (RoomsMap[i-1][j]) { // Left Room
            count++;
        }
    }

    if(j > 0){
        if (RoomsMap[i][j-1]) { // Room above
            count++;
        }
    }

    if(i+1 < maxSize){
       if(RoomsMap[i+1][j]){ // Right Room
           count++;
       }
    }

    if(j+1 < maxSize){
        if(RoomsMap[i][j+1]){ // Room below
            count++;
        }
    }

    return (count == 1);
}

/****************
 * Graphic View *
 ***************/

std::ostream& operator<<(std::ostream& stream, const Stage& d){

	for (unsigned i = 0; i < d.getSize(); i++)
	{
		for (unsigned j = 0; j < d.getSize(); j++)
		{
			if (d.getRoom(i, j) == nullptr)
			{
				stream << ".";
			}
			else
			{
				switch (d.getRoom(i, j)->getType())
				{
					case roomType::Common:
						stream << "c";
						break;
					
					case roomType::Start:
						stream << "S";
						break;
					
					case roomType::Boss:
						stream << "B";
						break;

				    case roomType::CommonStart:
				        stream << "s";
                        break;

				    case roomType::Room2WE1 :
                        stream << "x";
                        break;


				    case roomType::Room2WE2 :
                        stream << "x";
                        break;


				    case roomType::Room2NS1 :
                        stream << "x";
                        break;


				    case roomType::Room2NS2 :
                        stream << "x";
                        break;


                    case roomType::Room4NESW:
                        stream << "x";
                        break;


				    case roomType::Room1N:
                        stream << "x";
                        break;


                    case roomType::Room1E:
                        stream << "x";
                        break;


                    case roomType::Room1S:
                        stream << "x";
                        break;


				    case roomType::Room1W :
                        stream << "x";
                        break;


                    case roomType::Room3NEW:
                        stream << "x";
                        break;

                    case roomType::Room3NSW:
                        stream << "x";
                        break;

				    case roomType::Room3ESW:
                        stream << "x";
                        break;

                    case roomType::Room3NES:
                        stream << "x";
                        break;
					
					default:
						break;
				}
			}
		}
		
		stream << std::endl;
	}
	
	return stream;
}
