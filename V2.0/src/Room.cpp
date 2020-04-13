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

void Room::fillBoss(unsigned idMonst) {
    monsters.push_back(new Entity(MonsterBoss[0], MonsterBoss[1], idMonst));
}

void Room::fillMonsters(std::vector<unsigned int> idMonst, roomType t) {
    for(unsigned i = 0; i < idMonst.size(); ++i){
        if(idMonst[i]){
            switch (t){
                case Room2NS1:
                    monsters.push_back(new Entity(Monster2NS1[i][0], Monster2NS1[i][1], idMonst[i]));
                    break;

                case Room2NS2:
                    monsters.push_back(new Entity(Monster2NS2[i][0], Monster2NS2[i][1], idMonst[i]));
                    break;

                case Room2WE1:
                    monsters.push_back(new Entity(Monster2WE1[i][0], Monster2WE1[i][1], idMonst[i]));
                    break;

                case Room2WE2:
                    monsters.push_back(new Entity(Monster2WE2[i][0], Monster2WE2[i][1], idMonst[i]));
                    break;

                case Room4NESW1:
                    monsters.push_back(new Entity(Monster4NESW1[i][0], Monster4NESW1[i][1], idMonst[i]));
                    break;

                case Room4NESW2:
                    monsters.push_back(new Entity(Monster4NESW2[i][0], Monster4NESW2[i][1], idMonst[i]));
                    break;

                case Room1N:
                    monsters.push_back(new Entity(Monster1N[i][0], Monster1N[i][1], idMonst[i]));
                    break;

                case Room1E:
                    monsters.push_back(new Entity(Monster1E[i][0], Monster1E[i][1], idMonst[i]));
                    break;

                case Room1S:
                    monsters.push_back(new Entity(Monster1S[i][0], Monster1S[i][1], idMonst[i]));
                    break;

                case Room1W:
                    monsters.push_back(new Entity(Monster1W[i][0], Monster1W[i][1], idMonst[i]));
                    break;

                case Room3NES:
                    monsters.push_back(new Entity(Monster3NES[i][0], Monster3NES[i][1], idMonst[i]));
                    break;

                case Room3ESW:
                    monsters.push_back(new Entity(Monster3ESW[i][0], Monster3ESW[i][1], idMonst[i]));
                    break;

                case Room3NSW:
                    monsters.push_back(new Entity(Monster3NSW[i][0], Monster3NSW[i][1], idMonst[i]));
                    break;

                case Room3NEW:
                    monsters.push_back(new Entity(Monster3NEW[i][0], Monster3NEW[i][1], idMonst[i]));
                    break;

                default:
                    break;
            }
        }
    }
}

void Room::fillRocks(roomType t) {
    switch (t){
        case roomType::Room2WE1 :
            for(unsigned i = 0; i < 24; ++i){
                rocks.push_back(Rock(Rocks2WE1[i][0], Rocks2WE1[i][1]));
            }
            break;

        case roomType::Room4NESW2:
            for(unsigned i = 0; i < 24; ++i){
                rocks.push_back(Rock(Rocks4NESW2[i][0], Rocks4NESW2[i][1]));
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

void Room::fillChest(std::vector<unsigned> Ids) {
    chest = new Chest(hero, Chest::orientation::South);
    for(unsigned i = 0; i < Ids.size(); ++i){
        chest->addInChest(Ids[i]);
    }
}

std::vector<Door*> Room::getDoors() const {
    return Doors;
}

std::vector<Entity*> Room::getMonsters() const {
    return monsters;
}

std::vector<Rock> Room::getRocks() const {
    return rocks;
}

Chest* Room::getChest() const {
    return chest;
}
