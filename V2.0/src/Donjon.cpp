#include "Donjon.h"

Donjon::Donjon(unsigned stageNumb, Entity& aspen):
        hero(aspen),
        stageNb(stageNumb),
        stage(0),
        currentStage(new Stage(hero)){

    currentStage->generate(stage);
    currentStage->affectRoomTypeMonsterObject();

    std::cout << currentStage;
}

Stage* Donjon::getCurrentStage() const {
    return currentStage;
}
/* A ADAPTER POUR LA SFML
std::array< std::array<char, 27>, 27> Donjon::RoomCoordToChar(unsigned i, unsigned j) {

    Room *room = currentStage->getRoom(i, j);

    switch (room->getType()){

        case roomType::Start: case roomType::CommonStart:
            return placeRoomDoors(room, start);

        case roomType::Boss:
            return placeRoomDoors(room, boss);

        case roomType::Room2WE1:
            return room2WE1;

        case roomType::Room2WE2:
            return room2WE2;

        case roomType::Room2NS1:
            return room2NS1;

        case roomType::Room2NS2:
            return room2NS2;

        case roomType::Room4NESW:
            return placeRoomDoors(room, room4NESW);

        case roomType::Room1N:
            return room1N;

        case roomType::Room1E:
            return room1E;

        case roomType::Room1S:
            return room1S;

        case roomType::Room1W:
            return room1W;

        case roomType::Room3NEW:
            return room3NEW;

        case roomType::Room3NSW:
            return room3NSW;

        case roomType::Room3ESW:
            return room3ESW;

        case roomType::Room3NES:
            return room3NES;

        default:
            throw std::runtime_error {"Donjon::RoomCoordToChar - Impossible de trouver la salle"};
    }


}*/

unsigned Donjon::getStage() {
    return stage;
}

void Donjon::nextStage() {
    if(stage < stageNumber){
        stage++;
        currentStage->generate(stage);
        currentStage->affectRoomTypeMonsterObject();
    }
    else
        std::cout << "Fin du Donjon" << std::endl;
        //throw std::runtime_error {"Donjon::nextStage(" + std::to_string(stage) + ") - Bravo ! Vous êtes arrivé à bout de ce donjon !"};

}
/* A ADAPTER POUR LA SFML
std::array< std::array<char, 27>, 27> Donjon::placeRoomDoors(Room *curRoom, std::array< std::array<char, 27>, 27> room) {

    for(unsigned i = 0 ; i < 4; i++){
        switch (i){
            case 0: // North
                if(curRoom->getDoor(i)){
                    std::cout << "0" << std::endl;
                    for(unsigned b = 12; b < 15; b++){
                        room[1][b] = '8';
                    }
                }
                break;

            case 1: // East
                if(curRoom->getDoor(i)){
                    std::cout << "1" << std::endl;
                    for(unsigned a = 12; a < 15; a++){
                        room[a][25] = '8';
                    }
                }
                break;

            case 2: // South
                if(curRoom->getDoor(i)){
                    std::cout << "2" << std::endl;
                    for(unsigned b = 12; b < 15; b++){
                        room[25][b] = '8';
                    }
                }
                break;

            case 3: // West
                if(curRoom->getDoor(i)){
                    std::cout << "3" << std::endl;
                    for(unsigned a = 12; a < 15; a++){
                        room[a][1] = '8';
                    }
                }
                break;

            default:
                throw std::runtime_error {"Donjon::placeRoomDoors - Impossible de placer des portes"};
        }
    }
    return room;
}

std::ostream& operator<<(std::ostream& stream, const std::array< std::array<char, 27>, 27>& d){

    for(unsigned i = 0; i < 27; ++i){
        for(unsigned j = 0; j < 27; ++j){
            stream << d[i][j];
        }
        stream << std::endl;
    }

    return stream;
}*/
