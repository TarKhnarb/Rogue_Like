#include "Room.h"

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
    monsters.push_back(new Entity(Archetype::MonsterBoss[0], Archetype::MonsterBoss[1], idMonst));
}

void Room::fillMonsters(std::vector<unsigned int> idMonst, roomType t) {
    for(unsigned i = 0; i < idMonst.size(); ++i){
        if(idMonst[i]){
            switch (t){
                case Room2NS1:
                    monsters.push_back(new Entity(Archetype::Monster2NS1[i][0], Archetype::Monster2NS1[i][1], idMonst[i]));
                    break;

                case Room2NS2:
                    monsters.push_back(new Entity(Archetype::Monster2NS2[i][0], Archetype::Monster2NS2[i][1], idMonst[i]));
                    break;

                case Room2WE1:
                    monsters.push_back(new Entity(Archetype::Monster2WE1[i][0], Archetype::Monster2WE1[i][1], idMonst[i]));
                    break;

                case Room2WE2:
                    monsters.push_back(new Entity(Archetype::Monster2WE2[i][0], Archetype::Monster2WE2[i][1], idMonst[i]));
                    break;

                case Room4NESW1:
                    monsters.push_back(new Entity(Archetype::Monster4NESW1[i][0], Archetype::Monster4NESW1[i][1], idMonst[i]));
                    break;

                case Room4NESW2:
                    monsters.push_back(new Entity(Archetype::Monster4NESW2[i][0], Archetype::Monster4NESW2[i][1], idMonst[i]));
                    break;

                case Room1N:
                    monsters.push_back(new Entity(Archetype::Monster1N[i][0], Archetype::Monster1N[i][1], idMonst[i]));
                    break;

                case Room1E:
                    monsters.push_back(new Entity(Archetype::Monster1E[i][0], Archetype::Monster1E[i][1], idMonst[i]));
                    break;

                case Room1S:
                    monsters.push_back(new Entity(Archetype::Monster1S[i][0], Archetype::Monster1S[i][1], idMonst[i]));
                    break;

                case Room1W:
                    monsters.push_back(new Entity(Archetype::Monster1W[i][0], Archetype::Monster1W[i][1], idMonst[i]));
                    break;

                case Room3NES:
                    monsters.push_back(new Entity(Archetype::Monster3NES[i][0], Archetype::Monster3NES[i][1], idMonst[i]));
                    break;

                case Room3ESW:
                    monsters.push_back(new Entity(Archetype::Monster3ESW[i][0], Archetype::Monster3ESW[i][1], idMonst[i]));
                    break;

                case Room3NSW:
                    monsters.push_back(new Entity(Archetype::Monster3NSW[i][0], Archetype::Monster3NSW[i][1], idMonst[i]));
                    break;

                case Room3NEW:
                    monsters.push_back(new Entity(Archetype::Monster3NEW[i][0], Archetype::Monster3NEW[i][1], idMonst[i]));
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
                rocks.push_back(Rock(Archetype::Rocks2WE1[i][0], Archetype::Rocks2WE1[i][1]));
            }
            break;

        case roomType::Room4NESW2:
            for(unsigned i = 0; i < 24; ++i){
                rocks.push_back(Rock(Archetype::Rocks4NESW2[i][0], Archetype::Rocks4NESW2[i][1]));
            }
            break;

        case roomType::Room1N:
            for(unsigned i = 0; i < 8; ++i){
                rocks.push_back(Rock(Archetype::Rocks1N[i][0], Archetype::Rocks1N[i][1]));
            }
            break;

        case roomType::Room1S:
            for(unsigned i = 0; i < 16; ++i){
                rocks.push_back(Rock(Archetype::Rocks1S[i][0], Archetype::Rocks1S[i][1]));
            }
            break;

        case roomType::Room1W:
            for(unsigned i = 0; i < 31; ++i){
                rocks.push_back(Rock(Archetype::Rocks1W[i][0], Archetype::Rocks1W[i][1]));
            }
            break;

        case roomType::Room3NSW:
            for(unsigned i = 0; i < 11; ++i){
                rocks.push_back(Rock(Archetype::Rocks3NSW[i][0], Archetype::Rocks3NSW[i][1]));
            }
            break;

        case roomType::Room3NEW:
            for(unsigned i = 0; i < 7; ++i){
                rocks.push_back(Rock(Archetype::Rocks3NEW[i][0], Archetype::Rocks3NEW[i][1]));
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
            throw std::runtime_error ("Room::getStringType(roomType type) const - Sélectionnez un type valide");
    }
}