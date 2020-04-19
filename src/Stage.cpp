#include "Stage.h"

/****************
 * Constructeur *
 ***************/

Stage::Stage(Entity & aspen):
        hero(aspen){
    
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

/**************
 * Destructor *
 *************/

Stage::~Stage(){
    for(unsigned i = 0; i < maxSize; i++){
        for (unsigned j = 0; j < maxSize; j++){
			if(RoomsMap[i][j]){
                delete RoomsMap[i][j];
                RoomsMap[i][j] = nullptr;
			}
        }
    }
}

/************
 * Generate *
 ***********/

void Stage::generate(unsigned &stage){
	
    if(random) seed = time(0);
	srand(seed);

	roomsNb = rand()%(maxRooms-minRooms+1)+minRooms;

    unsigned mid = (maxSize - 1)/2;
	
	unsigned roomsCnt = 0; // Compteur de salles posées
	unsigned density = 2; // >= 2, traduit la densité des cases (plus elle est élévée, plus on s'assure de poser assez de salles)
	
	while (roomsNb != roomsCnt){ // Génère les salles autour de la salle de départ (centre)

	    reset(stage); // Reset (nettoie le tableau et genere le depart au milieu du tableau)
        roomsCnt = 0; // Au cas où on recommence

		// Génère les salles du Stage
        for (unsigned k = 1; k <= mid; k++) // Chaque 'cercles' autour du point central
        {
            for (unsigned i = mid-k+1; i <= mid+k; i++) // Première ligne, en haut à l'horizontal, sauf case tout en haut à gauche (car rien encore à côté)
            {
                if ((i > 0 && RoomsMap[i-1][mid-k]) || RoomsMap[i][mid-k+1]) // Test sur les cases à gauche et en dessous
                {
                    if (roomsCnt < roomsNb-1 && rand()%density == density - 1) // Place une salle seulement si le mod est différent de 0
					// on écrit roomsNb-1 car on garde une salle pour le boss
                    {
                        RoomsMap[i][mid-k] = new Room(Common, hero);
                        roomsCnt ++;
                    }
                }
            }

            if (RoomsMap[mid-k+1][mid-k]){ // Traitement de la case tout en haut à gauche

                if(roomsCnt < roomsNb-1 && rand()%density == density - 1)
                {
                    RoomsMap[mid-k][mid-k] = new Room(Common, hero);
                    roomsCnt ++;
                }
            }

            for (unsigned j = mid-k+1; j <= mid+k-1; j++) // Deuxième ligne, à droite à la verticale
            {
                if ((j > 0 && RoomsMap[mid+k][j-1]) || RoomsMap[mid+k-1][j]) // Test sur les cases au dessus et à gauche
                {
                    if (roomsCnt < roomsNb-1 && rand()%density == density - 1)
                    {
                        RoomsMap[mid+k][j] = new Room(Common, hero);
                        roomsCnt ++;
                    }
                }
            }

            for (unsigned j = mid-k+1; j <= mid+k-1; j++) // Troisième ligne, à gauche à la verticale
            {
                if ((j > 0 && RoomsMap[mid-k][j-1]) || RoomsMap[mid-k+1][j]) // test sur les cases au dessus et à droite
                {
                    if (roomsCnt < roomsNb-1 && rand()%density == density - 1)
                    {
                        RoomsMap[mid-k][j] = new Room(Common, hero);
                        roomsCnt ++;
                    }
                }
            }

            for (unsigned i = mid-k; i <= mid+k; i++) // Dernière ligne, en bas à l'horizontal
            {
                if ((i+1 < maxSize && RoomsMap[i+1][mid+k]) || RoomsMap[i][mid+k-1]) // Test de la case à gauche et au dessus
                {
                    if (roomsCnt < roomsNb-1 && rand()%density == density - 1)
                    {
                        RoomsMap[i][mid+k] = new Room(Common, hero);
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
                        if (roomsCnt == roomsNb-1 && rand()%density == density - 1) // Place une salle seulement si le mod est différent de 0
                        {
                            RoomsMap[i][mid-k] = new Room(Boss, hero);
                            roomsCnt ++;
                        }
                    }
                }

                if (!RoomsMap[mid-k][mid-k] && countRoomsAround(mid-k, mid-k)){ // Traitement de la case tout en haut à gauche
                    if(roomsCnt == roomsNb-1 && rand()%density == density - 1)
                    {
                        RoomsMap[mid-k][mid-k] = new Room(Boss, hero);
                        roomsCnt ++;
                    }
                }

                for (unsigned j = mid-k+1; j <= mid+k-1; j++) // Deuxième ligne, à droite à la verticale
                {
                    if (!RoomsMap[mid+k][j] && countRoomsAround(mid+k, j))
                    {
                        if (roomsCnt == roomsNb-1 && rand()%density == density - 1)
                        {
                            RoomsMap[mid+k][j] = new Room(Boss, hero);
                            roomsCnt ++;
                        }
                    }
                }

                for (unsigned j = mid-k+1; j <= mid+k-1; j++) // Troisième ligne, à gauche à la verticale
                {
                    if (!RoomsMap[mid-k][j] && countRoomsAround(mid-k, j))
                    {
                        if (roomsCnt == roomsNb-1 && rand()%density == density - 1)
                        {
                            RoomsMap[mid-k][j] = new Room(Boss, hero);
                            roomsCnt ++;
                        }
                    }
                }

                for (unsigned i = mid-k; i <= mid+k; i++) // Dernière ligne, en bas à l'horizontal
                {
                    if (!RoomsMap[i][mid+k] && countRoomsAround(i, mid+k))
                    {
                        if (roomsCnt == roomsNb-1 && rand()%density == density - 1)
                        {
                            RoomsMap[i][mid+k] = new Room(Boss, hero);
                            roomsCnt ++;
                        }
                    }
                }
            }
        }
	}

	placeDoors();
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
 * Get Room *
 ***********/

Room* Stage::getRoom(unsigned i, unsigned j){
    return RoomsMap[i][j];
}

/***************
 * Place Doors *
 **************/

void Stage::placeDoors(){

    for(unsigned i = 0; i < maxSize; i++){
        for(unsigned j = 0; j < maxSize; j ++){
            if(RoomsMap[i][j]){
                if (i > 0 && RoomsMap[i-1][j]) { // Room above
                    RoomsMap[i][j]->placeDoor(0);
                }

                if (j > 0 && RoomsMap[i][j-1]) { // Left Room
                    RoomsMap[i][j]->placeDoor(3);
                }

                if(i+1 < maxSize && RoomsMap[i+1][j]){ // Room below
                    RoomsMap[i][j]->placeDoor(2);
                }

                if(j+1 < maxSize && RoomsMap[i][j+1]){ // Right Room
                    RoomsMap[i][j]->placeDoor(1);
                }
            }
        }
     }
}


void Stage::affectRoomTypeMonsterObject(){

    for(unsigned i = 0; i < maxSize; i++){
        for(unsigned j = 0; j < maxSize; j++){

                // Affectation des types de salles, rochers, monstres et coffres
            if(RoomsMap[i][j] && RoomsMap[i][j]->getType() == roomType::Common){
                switch (RoomsMap[i][j]->getDoorsNb()){
                    case 1:
                        if(RoomsMap[i][j]->getDoor(0)){ // Doors at North
                            RoomsMap[i][j]->setType(Room1N);
                            RoomsMap[i][j]->fillRocks(Room1N);
                            RoomsMap[i][j]->fillMonsters(randomMonsters(), Room1N);
                            RoomsMap[i][j]->fillChest(randomObjects(randomObjectWithProbability()));
                        }

                        if(RoomsMap[i][j]->getDoor(1)){ // Doors at East
                            RoomsMap[i][j]->setType(Room1E);
                            RoomsMap[i][j]->fillMonsters(randomMonsters(), Room1E);
                            RoomsMap[i][j]->fillChest(randomObjects(randomObjectWithProbability()));
                        }

                        if(RoomsMap[i][j]->getDoor(2)){ // Doors at South
                            RoomsMap[i][j]->setType(Room1S);
                            RoomsMap[i][j]->fillMonsters(randomMonsters(), Room1S);
                            RoomsMap[i][j]->fillRocks(Room1S);
                            RoomsMap[i][j]->fillChest(randomObjects(randomObjectWithProbability()));
                        }

                        if(RoomsMap[i][j]->getDoor(3)){ // Doors at West
                            RoomsMap[i][j]->setType(Room1W);
                            RoomsMap[i][j]->fillMonsters(randomMonsters(), Room1W);
                            RoomsMap[i][j]->fillRocks(Room1W);
                            RoomsMap[i][j]->fillChest(randomObjects(randomObjectWithProbability()));
                        }
                        break;

                    case 2:
                        if(RoomsMap[i][j]->getDoor(0) && RoomsMap[i][j]->getDoor(2)){ // Doors at North South
                            if((rand()%seed) % 2){
                                RoomsMap[i][j]->setType(Room2NS1);
                                RoomsMap[i][j]->fillMonsters(randomMonsters(), Room2NS1);
                            }
                            else{
                                RoomsMap[i][j]->setType(Room2NS2);
                                RoomsMap[i][j]->fillMonsters(randomMonsters(), Room2NS2);
                            }
                        }

                        if(RoomsMap[i][j]->getDoor(1) && RoomsMap[i][j]->getDoor(3)){ // Doors at West East 1
                            if((rand()%seed) % 2){
                                RoomsMap[i][j]->setType(Room2WE1);
                                RoomsMap[i][j]->fillMonsters(randomMonsters(), Room2WE1);
                                RoomsMap[i][j]->fillRocks(Room2WE1);
                            }
                            else{
                                RoomsMap[i][j]->setType(Room2WE2);
                                RoomsMap[i][j]->fillMonsters(randomMonsters(), Room2WE2);
                            }
                        }

                        if(RoomsMap[i][j]->getDoor(0) && RoomsMap[i][j]->getDoor(1)){ // Doors at North East
                            RoomsMap[i][j]->setType(Room4NESW2);
                            RoomsMap[i][j]->fillMonsters(randomMonsters(), Room4NESW2);
                            RoomsMap[i][j]->fillRocks(Room4NESW2);
                        }

                        if(RoomsMap[i][j]->getDoor(0) && RoomsMap[i][j]->getDoor(3)){ // Doors at North West
                            RoomsMap[i][j]->setType(Room4NESW2);
                            RoomsMap[i][j]->fillMonsters(randomMonsters(), Room4NESW2);
                            RoomsMap[i][j]->fillRocks(Room4NESW2);
                        }

                        if(RoomsMap[i][j]->getDoor(1) && RoomsMap[i][j]->getDoor(2)){ // Doors at South East
                            RoomsMap[i][j]->setType(Room4NESW2);
                            RoomsMap[i][j]->fillMonsters(randomMonsters(), Room4NESW2);
                            RoomsMap[i][j]->fillRocks(Room4NESW2);
                        }

                        if(RoomsMap[i][j]->getDoor(2) && RoomsMap[i][j]->getDoor(3)){ // Doors at South West
                            RoomsMap[i][j]->setType(Room4NESW2);
                            RoomsMap[i][j]->fillMonsters(randomMonsters(), Room4NESW2);
                            RoomsMap[i][j]->fillRocks(Room4NESW2);
                        }
                        break;

                    case 3:
                        if(rand()%4) { // 3 chance sur 4

                            if(!RoomsMap[i][j]->getDoor(3)){ // Doors at North, East, South
                                RoomsMap[i][j]->setType(Room3NES);
                                RoomsMap[i][j]->fillMonsters(randomMonsters(), Room3NES);
                            }

                            if(!RoomsMap[i][j]->getDoor(0)){ // Doors at East, South, West
                                RoomsMap[i][j]->setType(Room3ESW);
                                RoomsMap[i][j]->fillMonsters(randomMonsters(), Room3ESW);
                                RoomsMap[i][j]->fillChest(randomObjects(randomObjectWithProbability()));
                            }

                            if(!RoomsMap[i][j]->getDoor(1)){ // Doors at North, South, West
                                RoomsMap[i][j]->setType(Room3NSW);
                                RoomsMap[i][j]->fillMonsters(randomMonsters(), Room3NSW);
                                RoomsMap[i][j]->fillRocks(Room3NSW);
                            }

                            if(!RoomsMap[i][j]->getDoor(2)){ // Doors at North, East, West
                                RoomsMap[i][j]->setType(Room3NEW);
                                RoomsMap[i][j]->fillMonsters(randomMonsters(), Room3NEW);
                                RoomsMap[i][j]->fillRocks(Room3NEW);
                            }
                        }
                        else{
                            RoomsMap[i][j]->setType(Room4NESW2);
                            RoomsMap[i][j]->fillMonsters(randomMonsters(), Room4NESW2);
                            RoomsMap[i][j]->fillRocks(Room4NESW2);
                        }


                        break;
                    case 4:

                        if(rand()%2 == 0) {
                            RoomsMap[i][j]->setType(Room4NESW1);
                            RoomsMap[i][j]->fillMonsters(randomMonsters(), Room4NESW1);

                        }
                        else{
                            RoomsMap[i][j]->setType(Room4NESW2);
                            RoomsMap[i][j]->fillMonsters(randomMonsters(), Room4NESW2);
                            RoomsMap[i][j]->fillRocks(Room4NESW2);
                        }

                        break;

                    default:
                        break;
                }
            }

            if(RoomsMap[i][j] && RoomsMap[i][j]->getType() == roomType::Boss){
                RoomsMap[i][j]->fillBoss((seed%4)+7); // Tire un id entre 7 et 10
            }
        }
    }
}

/*********
 * Reset *
 ********/

void Stage::reset(unsigned stage) {

    for(unsigned i = 0; i < maxSize; i++) {
        for (unsigned j = 0; j < maxSize; j++) {
			if (RoomsMap[i][j]){
                delete RoomsMap[i][j];
                RoomsMap[i][j] = nullptr;
			}
        }
    }

    unsigned mid = (maxSize - 1)/2;
    RoomsMap[mid][mid] = new Room(roomType::Start, hero);
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

std::vector<unsigned int> Stage::randomObjects(unsigned nb) {

    std::vector<unsigned> obj;
    for(unsigned i = 0; i < nb; ++i){
        obj.push_back((rand()%15)+50); // permet de tirer l'id d'un object entre 50 et 64
    }

    return obj;
}

std::vector<unsigned int> Stage::randomMonsters() {

    std::vector<unsigned> monst;
    unsigned nb = (rand()%5) + 2; // On tire entre 2 et 6 monstres
    for(unsigned i = 0; i < nb; ++i){
        monst.push_back((rand()%5)+2); // permet de tirer un id de monstre entre 2 et 6
    }

    return monst;
}

unsigned Stage::randomObjectWithProbability() {

    unsigned random = (rand()%3) + 1; // valeur entre 1 et 3

    if(random == 1)
        return 2;
    else
        return 1;
}

std::vector<Door *> Stage::getDoors(unsigned i, unsigned j) const {
    return RoomsMap[i][j]->getDoors();
}

std::vector<Entity *> Stage::getMonsters(unsigned i, unsigned j) const {
    return RoomsMap[i][j]->getMonsters();
}

std::vector<Rock> Stage::getRocks(unsigned i, unsigned j) const {
    return RoomsMap[i][j]->getRocks();
}

Chest* Stage::getChest(unsigned i, unsigned j) const {
    return RoomsMap[i][j]->getChest();
}

/****************
 * Graphic View *
 ***************/

std::ostream& operator<<(std::ostream& stream, Stage *s){

	for (unsigned i = 0; i < maxSize; i++){
		for (unsigned j = 0; j < maxSize; j++){
			if (s->getRoom(i, j) == nullptr){
				stream << ".";
			}
			else{
				switch (s->getRoom(i, j)->getType()){
					case roomType::Common:
						stream << "c";
						break;
					
					case roomType::Start:
						stream << "S";
						break;
					
					case roomType::Boss:
						stream << "Z";
						break;

				    case roomType::CommonStart:
				        stream << "s";
                        break;

				    case roomType::Room2WE1 :
                        stream << "A";
                        break;

				    case roomType::Room2WE2 :
                        stream << "B";
                        break;

				    case roomType::Room2NS1 :
                        stream << "C";
                        break;

				    case roomType::Room2NS2 :
                        stream << "D";
                        break;

                    case roomType::Room4NESW1:
                        stream << "E";
                        break;

				    case roomType::Room4NESW2:
				        stream << "F";
                        break;

				    case roomType::Room1N:
                        stream << "G";
                        break;

                    case roomType::Room1E:
                        stream << "H";
                        break;

                    case roomType::Room1S:
                        stream << "I";
                        break;

				    case roomType::Room1W :
                        stream << "J";
                        break;

                    case roomType::Room3NEW:
                        stream << "K";
                        break;

                    case roomType::Room3NSW:
                        stream << "L";
                        break;

				    case roomType::Room3ESW:
                        stream << "M";
                        break;

                    case roomType::Room3NES:
                        stream << "N";
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
