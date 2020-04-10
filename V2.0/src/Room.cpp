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
        hero(apsen){}

/**************
 * Destructor *
 *************/

Room::~Room() {
    for(int i = 0; i < 4 ; i++){
		delete Doors[i];
        Doors[i] = nullptr;
    }

    for(auto monster : monsters){
        delete monster;
        monster = nullptr;
    }

    for(auto rock : rocks){
        delete rock;
        rock = nullptr;
    }

    for(auto ches : chest){
        delete ches;
        ches = nullptr;
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

void Room::fillMonsters(std::vector<unsigned int> idMonst) {
/*    for(auto id : idMonst){
        monsters.push_back(Entity(id))
    }*/
}

void Room::fillRocks(roomType t) {
    switch (t){
        case roomType::Room2WE1 :
            for(unsigned i = 0; i < 24; ++i){
                rocks->pos(Rocks2WE1[i][0], Rocks2WE1[i][1]);
            }
            break;
        default:
            break;
    }
}

void Room::fillChest(std::vector<unsigned int> Ids) {
    for(auto id : Ids){
        chest = new Chest().addInChest(id);
    }
}
