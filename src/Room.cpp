#include "Room.h"

Room::Room(){

    for(int i = 0; i < 4; i++){
        Doors[i] = nullptr;
    }

    type = roomType::Common;
}

Room::Room(roomType t) {
    for(int i = 0; i < 4; i++){
        Doors[i] = nullptr;
    }

    type = t;
}

Room::~Room() {
    for(int i = 0; i < 4 ; i++) {
        delete Doors[i];
        Doors[i] = nullptr;
    }
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


int Room::getDoorsNb() const{
    int i = 0;
    for(int j = 0; j < 4; j++){
        if(Doors[i] != nullptr) i++;
    }

    return i;
}


roomType Room::getType() const{
    return type;
};

void Room::setType(roomType i){
    type = i;
}

void Room::placeDoor(int i) {
    delete Doors[i];
    Doors[i] = new Door();
}
