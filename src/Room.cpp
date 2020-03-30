#include "Room.h"

/***************
 * Constructor *
 **************/

Room::Room(){

    for(int i = 0; i < 4; i++){
        Doors[i] = nullptr;
    }

    type = roomType::Common;
}

/********************************
 * Constructor With Room's Type *
 *******************************/

Room::Room(roomType t) {
    for(int i = 0; i < 4; i++){
        Doors[i] = nullptr;
    }

    type = t;
}

/**************
 * Destructor *
 *************/

Room::~Room() {
    for(int i = 0; i < 4 ; i++){
		delete Doors[i];
        Doors[i] = nullptr;
    }
}

/**************
 * Open Doors *
 *************/

void Room::openDoors(){
    for(int i = 0; i < 4; i++){
        if((Doors[i]) && !(Doors[i]->getKey())) Doors[i]->setOpen(true);
    }
}

/***************
 * Close Doors *
 **************/

void Room::closeDoors(){
    for(int i = 0; i < 4; i++){
        if(Doors[i]) Doors[i]->setOpen(false);
    }
}

//          A faire
// void unlockDoor(Door); // Ouvre une porte qui necessite une clé et que le joueur en possède une

/***************
 * Unlock Door *
 **************/

void Room::unlockDoor(int i) {
    if(Doors[i]->getKey() && ! Doors[i]->getOpen()){
        Doors[i]->setKey(false);
        Doors[i]->setOpen(true);
    }
}

/*********************
 * Get Door's Number *
 ********************/
 
int Room::getDoorsNb() const{
    int i = 0;
    for(int j = 0; j < 4; j++){
        if(Doors[j]) i++;
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
