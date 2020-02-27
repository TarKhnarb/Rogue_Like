#include "Salle.h"

using namespace std;

Room::Room() {
    nbDoors = 0;

    for(int i = 0; i < 4; i++){
        Door[i].exist = false;
        Door[i].key = false;
        Door[i].open = false;
    }
    type = 0;
}

void Room::openDoors(){
    for(int i = 0; i < 4; i++){
        if(! Door[i].key){
            Door[i].open = true;
        }
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
