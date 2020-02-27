#include "Salle.h"

using namespace std;

Room::Room() {
    nbDoors = 0;
}

char Room::getTypeRoom(){
    return typeRoom;
};

void Room::setTypeRoom(char type){
    typeRoom = type;
}

int Donjon::countDoor(Room tab) {
    for(int i = 0; i < Gmax; i++){

        for(int j = 0; j < Gmax; j++){

            if(tab[i][j] != 0){
                if(tab[i-1][j] != 0 || tab[i+1][j] != 0 || tab[i][j-1] != 0 || tab[i][j+1] != 0) {
                    tab[i][j].nbDoor++;
                    Room::Doors[0].exist = true;
                }
            }
        }
    }
}
