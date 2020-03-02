#include "Room.h"
#include "assert.h"

Room::Room(){

    doorsNb = 0;

    for(int i = 0; i < 4; i++){
        Doors[i] = new Door();
    }

    type = roomType::None;
}

Room::~Room() {
    for(int i = 0; i < 4 ; i++){
        Doors[i] = nullptr;
    }
    delete [] Doors;
}

void Room::openDoors(){
    for(int i = 0; i < 4; i++){
        if(! Doors[i]->Door::getKey())
        Doors[i]->openIt();
    }
}

void Room::closeDoors(){
    for(int i = 0; i < 4; i++){
        Doors[i]->closeIt();
    }
}

//          A faire
// void unlockDoor(Door); // Ouvre une porte qui necessite une clé et que le joueur en possède une


void Room::setDoorsNb(int i){
    doorsNb = i;
}

int Room::getDoorsNb(){
    return doorsNb;
}


int Room::getType(){
    return type;
};

void Room::setType(roomType i){
    type = i;
}

void Room::setDoorExist(int i, bool a){
    Doors[i]->setExist(a);
}