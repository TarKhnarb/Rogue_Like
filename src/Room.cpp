#include "Room.h"

/********************************
 * Constructor With Room's Type *
 *******************************/

Room::Room(roomType t, Entity *apsen):
        type(t),
        hero(apsen),
        Doors(4, nullptr),
        chest(nullptr){}

/**************
 * Destructor *
 *************/

Room::~Room() {
    for(auto it = Doors.begin(); it != Doors.end(); ++it){
        if(*it){
            delete *it;
            *it = nullptr;
        }
    }
    
    for(auto it = monsters.begin(); it != monsters.end(); ++it){
        if(*it){
            delete *it;
            *it = nullptr;
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
    monsters.push_back(new Entity(arch.MonsterBoss[0], arch.MonsterBoss[1], idMonst));
}

void Room::fillMonsters(std::vector<unsigned int> idMonst, roomType t) {
    for(unsigned i = 0; i < idMonst.size(); ++i){
        if(idMonst[i]){
            switch (t){
                case Room2NS1:
                    monsters.push_back(new Entity(arch.Monster2NS1[i][0], arch.Monster2NS1[i][1], idMonst[i]));
                    break;

                case Room2NS2:
                    monsters.push_back(new Entity(arch.Monster2NS2[i][0], arch.Monster2NS2[i][1], idMonst[i]));
                    break;

                case Room2WE1:
                    monsters.push_back(new Entity(arch.Monster2WE1[i][0], arch.Monster2WE1[i][1], idMonst[i]));
                    break;

                case Room2WE2:
                    monsters.push_back(new Entity(arch.Monster2WE2[i][0], arch.Monster2WE2[i][1], idMonst[i]));
                    break;

                case Room4NESW1:
                    monsters.push_back(new Entity(arch.Monster4NESW1[i][0], arch.Monster4NESW1[i][1], idMonst[i]));
                    break;

                case Room4NESW2:
                    monsters.push_back(new Entity(arch.Monster4NESW2[i][0], arch.Monster4NESW2[i][1], idMonst[i]));
                    break;

                case Room1N:
                    monsters.push_back(new Entity(arch.Monster1N[i][0], arch.Monster1N[i][1], idMonst[i]));
                    break;

                case Room1E:
                    monsters.push_back(new Entity(arch.Monster1E[i][0], arch.Monster1E[i][1], idMonst[i]));
                    break;

                case Room1S:
                    monsters.push_back(new Entity(arch.Monster1S[i][0], arch.Monster1S[i][1], idMonst[i]));
                    break;

                case Room1W:
                    monsters.push_back(new Entity(arch.Monster1W[i][0], arch.Monster1W[i][1], idMonst[i]));
                    break;

                case Room3NES:
                    monsters.push_back(new Entity(arch.Monster3NES[i][0], arch.Monster3NES[i][1], idMonst[i]));
                    break;

                case Room3ESW:
                    monsters.push_back(new Entity(arch.Monster3ESW[i][0], arch.Monster3ESW[i][1], idMonst[i]));
                    break;

                case Room3NSW:
                    monsters.push_back(new Entity(arch.Monster3NSW[i][0], arch.Monster3NSW[i][1], idMonst[i]));
                    break;

                case Room3NEW:
                    monsters.push_back(new Entity(arch.Monster3NEW[i][0], arch.Monster3NEW[i][1], idMonst[i]));
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
                rocks.push_back(Rock(arch.Rocks2WE1[i][0], arch.Rocks2WE1[i][1]));
            }
            break;

        case roomType::Room4NESW2:
            for(unsigned i = 0; i < 24; ++i){
                rocks.push_back(Rock(arch.Rocks4NESW2[i][0], arch.Rocks4NESW2[i][1]));
            }
            break;

        case roomType::Room1N:
            for(unsigned i = 0; i < 8; ++i){
                rocks.push_back(Rock(arch.Rocks1N[i][0], arch.Rocks1N[i][1]));
            }
            break;

        case roomType::Room1S:
            for(unsigned i = 0; i < 16; ++i){
                rocks.push_back(Rock(arch.Rocks1S[i][0], arch.Rocks1S[i][1]));
            }
            break;

        case roomType::Room1W:
            for(unsigned i = 0; i < 31; ++i){
                rocks.push_back(Rock(arch.Rocks1W[i][0], arch.Rocks1W[i][1]));
            }
            break;

        case roomType::Room3NSW:
            for(unsigned i = 0; i < 11; ++i){
                rocks.push_back(Rock(arch.Rocks3NSW[i][0], arch.Rocks3NSW[i][1]));
            }
            break;

        case roomType::Room3NEW:
            for(unsigned i = 0; i < 7; ++i){
                rocks.push_back(Rock(arch.Rocks3NEW[i][0], arch.Rocks3NEW[i][1]));
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

std::vector<Door*> Room::getDoors() {
    return Doors;
}

std::vector<Entity*>& Room::getMonsters() {
    return monsters;
}

std::vector<Rock>& Room::getRocks() {
    return rocks;
}

Chest* Room::getChest(){
    return chest;
}

std::string Room::getStringType() const{

    switch(type){
        case roomType::Start:
            return "RoomStart";

        case roomType::Boss:
            return "RoomBoss";

        case roomType::Room2WE1 :
            return "Room2WE1";

        case roomType::Room2WE2:
            return "Room2WE2";

        case roomType::Room2NS1:
            return "Room2NS1";

        case roomType::Room2NS2:
            return "Room2NS2";

        case roomType::Room4NESW1:
            return "Room4NESW1";

        case roomType::Room4NESW2:
            return "Room4NESW2";

        case roomType::Room1N:
            return "Room1N";

        case roomType::Room1E:
            return "Room1E";

        case roomType::Room1S:
            return "Room1S";

        case roomType::Room1W:
            return "Room1W";

        case roomType::Room3NEW:
            return "Room3NEW";

        case roomType::Room3NSW:
            return "Room3NSW";

        case roomType::Room3ESW:
            return "Room3ESW";

        case roomType::Room3NES:
            return "Room3NES";
        
        default:
            throw std::runtime_error ("CommonStart room is not playable");
    }
}
