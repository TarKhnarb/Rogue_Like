#include "Salle.h"

Room::Room() {
    doorsNb = 0;

    for(int i = 0; i < 4; i++){
        Doors[i] = Door();
    }
    type = 0;
}

void Room::openDoors(){
    for(int i = 0; i < 4; i++){
        Doors[i] = openIt();
    }
}

void Room::setDoorsNb(int i){
    doorsNb = i;
}


char Room::getType(){
    return type;
};

void Room::setType(int i){
    type = i;
}