#include "Room.h"

Room::Room() {

    doorsNb = 0;

    for(int i = 0; i < 4; i++){
        Doors[i] = Door();
    }

    type = Common;
}

void Room::openDoors(){
    for(int i = 0; i < 4; i++){
        Doors[i].openIt();
    }
}

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