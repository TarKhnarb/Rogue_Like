#include "Room.h"
#include "assert.h"

Room::Room(){

    for(int i = 0; i < 4; i++){
        Doors[i] = nullptr;
    }
}

Room::~Room() {
    for(int i = 0; i < 4 ; i++){
        Doors[i] = nullptr;
    }
    delete [] Doors;
}

void Room::openDoors(){
    for(int i = 0; i < 4; i++){
        if((Doors[i] != nullptr) && !(Doors[i]->getKey())) Doors[i]->setOpen(true);
    }
}

void Room::closeDoors(){
    for(int i = 0; i < 4; i++){
        if(Doors[i] != nullptr) Doors[i]->setOpen(false);
    }
}

//          A faire
// void unlockDoor(Door); // Ouvre une porte qui necessite une clé et que le joueur en possède une


int Room::getDoorsNb(){
    int i = 0;
    for(int j = 0; j < 4; j++){
        if(Doors[i] != nullptr) i++;
    }

    return i;
}


int Room::getType(){
    return type;
};

void Room::setType(roomType i){
    type = i;
}

void Room::placeDoor(int i) {
    Doors[i] = new Door();
}
