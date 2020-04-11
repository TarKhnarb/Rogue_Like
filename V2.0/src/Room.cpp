#include "Room.h"
#include "Archetype.h"

/***************
 * Constructor *
 **************/

Room::Room():
        type(roomType::Common),
        Doors(4, nullptr){}

/********************************
 * Constructor With Room's Type *
 *******************************/

Room::Room(roomType t, Entity &apsen):
        type(t),
        hero(apsen),
        Doors(4, nullptr){}

/**************
 * Destructor *
 *************/

Room::~Room() {
    for(int i = 0; i < 4 ; ++i){
        if(Doors[i]){
            delete Doors[i];
            Doors[i] = nullptr;
        }
    }

    for(auto monster : monsters){
        if(monster){
            delete monster;
            monster = nullptr;
        }
    }
    if(chest){
        delete chest;
        chest = nullptr;
    }
}

/**************
 * Open Doors *
 *************/

void Room::openDoors(){
    for(int i = 0; i < 4; ++i){
        if((Doors[i]))
            Doors[i]->setOpen(true);
    }
}

/***************
 * Close Doors *
 **************/

void Room::closeDoors(){
    for(int i = 0; i < 4; ++i){
        if(Doors[i]) Doors[i]->setOpen(false);
    }
}

/*********************
 * Get Door's Number *
 ********************/
 
int Room::getDoorsNb() const{
    int i = 0;
    for(int j = 0; j < 4; ++j){
        if(Doors[j])
            i++;
    }

    return i;
}

/************
 * Get Type *
 ***********/

roomType Room::getType() const{
    return type;
};

/************
 * Set Type *
 ***********/

void Room::setType(roomType i){
    type = i;
}

/****************
 * Place A Door *
 ***************/

void Room::placeDoor(unsigned i) {
	delete Doors[i];
	Doors[i] = nullptr;
	Doors[i] = new Door();
}

Door* Room::getDoor(unsigned i) {
    return Doors[i];
}

void Room::fillMonsters(std::vector<unsigned int> idMonst, roomType t) {
 /*   for(unsigned i = 0; i < idMonst.size(); ++i){
        if(idMonst[i]){
            switch (t){
                case Room2NS1:
                    monsters.push_back(new Entity(monster2NS1[i][0], monster2NS1[i][1], idMonst[i]));
                    break;

                case Room2NS2:
                    monsters.push_back(new Entity(monster2NS2[i][0], monster2NS2[i][1], idMonst[i]));
                    break;

                case Room2WE1:
                    monsters.push_back(new Entity(monster2WE1[i][0], monster2WE1[i][1], idMonst[i]));
                    break;

                case Room2WE2:
                    monsters.push_back(new Entity(monster2WE2[i][0], monster2WE2[i][1], idMonst[i]));
                    break;

                case Room1N:
                    monsters.push_back(new Entity(monster1N[i][0], monster1N[i][1], idMonst[i]));
                    break;

                case Room1E:
                    monsters.push_back(new Entity(monster1E[i][0], monster1E[i][1], idMonst[i]));
                    break;

                case Room1S:
                    monsters.push_back(new Entity(monster1S[i][0], monster1S[i][1], idMonst[i]));
                    break;

                case Room1W:
                    monsters.push_back(new Entity(monster1W[i][0], monster1W[i][1], idMonst[i]));
                    break;

                case Room3NES:
                    monsters.push_back(new Entity(monster3NES[i][0], monster3NES[i][1], idMonst[i]));
                    break;

                case Room3ESW:
                    monsters.push_back(new Entity(monster3ESW[i][0], monster3ESW[i][1], idMonst[i]));
                    break;

                case Room3NSW:
                    monsters.push_back(new Entity(monster3NSW[i][0], monster3NSW[i][1], idMonst[i]));
                    break;

                case Room3NEW:
                    monsters.push_back(new Entity(monster3NEW[i][0], monster3NEW[i][1], idMonst[i]));
                    break;

                case Room4NESW:
                    monsters.push_back(new Entity(monster4NESW[i][0], monster4NESW[i][1], idMonst[i]));
                    break;

                default:
                    break;
            }
        }
    }*/
}

void Room::fillRocks(roomType t) {
    switch (t){
        case roomType::Room2WE1 :
            for(unsigned i = 0; i < 24; ++i){
                rocks.push_back(Rock(Rocks2WE1[i][0], Rocks2WE1[i][1]));
            }
            break;

        case roomType::Room1N:
            for(unsigned i = 0; i < 8; ++i){
                rocks.push_back(Rock(Rocks1N[i][0], Rocks1N[i][1]));
            }
            break;

        case roomType::Room1S:
            for(unsigned i = 0; i < 16; ++i){
                rocks.push_back(Rock(Rocks1S[i][0], Rocks1S[i][1]));
            }
            break;

        case roomType::Room1W:
            for(unsigned i = 0; i < 31; ++i){
                rocks.push_back(Rock(Rocks1W[i][0], Rocks1W[i][1]));
            }
            break;

        case roomType::Room3NSW:
            for(unsigned i = 0; i < 11; ++i){
                rocks.push_back(Rock(Rocks3NSW[i][0], Rocks3NSW[i][1]));
            }
            break;

        case roomType::Room3NEW:
            for(unsigned i = 0; i < 7; ++i){
                rocks.push_back(Rock(Rocks3NEW[i][0], Rocks3NEW[i][1]));
            }
            break;

        default:
            break;
    }
}

void Room::fillChest(std::vector<unsigned int> Ids) {
    chest = new Chest(hero, Chest::orientation::South);
    for(auto id : Ids){
        chest->addInChest(id);
    }
}
