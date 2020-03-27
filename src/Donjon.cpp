#include "Donjon.h"
#include "rooms.h"

Donjon::Donjon(unsigned stageNumb){

    stageNb = stageNumb;
    stage = 0;
    currentStage = new Stage();

    currentStage->generate(stage);
    currentStage->affectRoomTypeMonsterObject();
}

Stage* Donjon::getCurrentStage(unsigned) const {
    return currentStage;
}

std::array< std::array<char, 27>, 27> Donjon::RoomCoordToChar(unsigned i, unsigned j) {

    Room *room = currentStage->getRoom(i, j);

    switch (room->getType()){

        case roomType::Start: case roomType::CommonStart:
            return placeRoomDoors(room, start);

        case roomType::Boss:
            return placeRoomDoors(room, boss);

        case roomType::Room2WE1:
            return placeRoomDoors(room, room2WE1);

        case roomType::Room2WE2:
            return placeRoomDoors(room, room2WE2);

        case roomType::Room2NS1:
            return placeRoomDoors(room, room2NS1);

        case roomType::Room2NS2:
            return placeRoomDoors(room, room2NS2);

        case roomType::Room4NESW:
            return placeRoomDoors(room, room4NESW);

        case roomType::Room1N:
            return placeRoomDoors(room, room1N);

        case roomType::Room1E:
            return placeRoomDoors(room, room1E);

        case roomType::Room1S:
            return placeRoomDoors(room, room1S);

        case roomType::Room1W:
            return placeRoomDoors(room, room1W);

        case roomType::Room3NEW:
            return placeRoomDoors(room, room3NEW);

        case roomType::Room3NSW:
            return placeRoomDoors(room,  room3NSW);

        case roomType::Room3ESW:
            return placeRoomDoors(room, room3ESW);

        case roomType::Room3NES:
            return placeRoomDoors(room, room3NES);

        default:
            throw std::runtime_error {"Donjon::RoomCoordToChar - Impossible de trouver la salle"};
    }


}

std::array< std::array<char, 27>, 27> Donjon::placeRoomDoors(Room *curRoom, std::array< std::array<char, 27>, 27> room) {

    for(unsigned i = 0 ; i < 4; ++i){
        switch (i){
            case 0:
                if(curRoom->getDoor(i)){
                    for(unsigned i = 12; i < 15; ++i){
                        room[i][1] = '8';
                    }
                }
                break;

            case 1:
                if(curRoom->getDoor(i)){
                    for(unsigned j = 12; j < 15; ++j){
                        room[25][j] = '8';
                    }
                }
                break;

            case 2:
                if(curRoom->getDoor(i)){
                    for(unsigned i = 12; i < 15; ++i){
                        room[i][25] = '8';
                    }
                }
                break;

            case 3:
                if(curRoom->getDoor(i)){
                    for(unsigned j = 12; j < 15; ++j){
                        room[1][j] = '8';
                    }
                }
                break;

            default:
                throw std::runtime_error {"Donjon::placeRoomDoors - Impossible de placer des portes"};
        }
    }
    return curRoom;
}
