#include "Stage.h"

#include <array>
#include <stdexcept>

const unsigned stageNumber = 6;

class Donjon{

public:

    Donjon(unsigned);
  //  Donjon(unsigned); // Pour commencer avec un seed précis

    Stage* getCurrentStage(unsigned) const;
    std::array< std::array<char, 27>, 27> RoomCoordToChar(unsigned, unsigned);

    void nextStage(); // Gère la création et l'incrémentation de l'étage suivant


private:

    std::array< std::array<char, 27>, 27> placeRoomDoors(Room*, std::array< std::array<char, 27>, 27>);

    unsigned stageNb;
    unsigned stage;
    unsigned seed;
    Stage *currentStage;
};