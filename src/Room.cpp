#include "Room.h"
#include "assert.h"

Room::Room(){

    doorsNb = 0;

    for(int i = 0; i < 4; i++){
        Doors[i] = new Door();
    }

    type = roomType::Common;
}

Room::~Room() {
    for(int i = 0; i < 4 ; i++){
        Doors[i] = nullptr;
    }
    delete [] Room::Doors;
}

void Room::openDoors(){
    for(int i = 0; i < 4; i++){
        if(! Doors[i]->Door::getKey())
        Doors[i]->Door::openIt();
    }
}

void Room::closeDoors(){
    for(int i = 0; i < 4; i++){
        Doors[i]->Door::closeIt();
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

bool Room::getDoorExist(int i){
    assert(i > 3 && i < 0);
    return  Doors[i]->getExist();
}
void Room::setDoorExist(int i, bool a){
    Doors[i]->setExist(a);
}