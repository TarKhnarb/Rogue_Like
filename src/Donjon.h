#include "Stage.h"
#include <array>

const unsigned stageNumber = 6;

class Donjon{

public:

    void placeCharInArray(char room[27][27], std::array< std::array<char, 27>, 27>);
    Donjon(unsigned);
  //  Donjon(unsigned); // Pour commencer avec un seed précis

    Stage* getCurrentStage(unsigned) const;
    std::array< std::array<char, 27>, 27> RoomCoordToChar(unsigned, unsigned);

    void nextStage(); // Gère la création et l'incrémentation de l'étage suivant


private:

    std::array< std::array<char, 27>, 27> placeRoomDoors(Room curRoom, char curRoom[27][27]);

    unsigned stageNb;
    unsigned stage;
    unsigned seed;
    Stage *currentStage;
     currentRoom;
};