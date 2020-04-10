#ifndef GAME_DONJON_H
#define GAME_DONJON_H

#include "Stage.h"
#include "Entity.h"

#include <array>
#include <stdexcept>
#include <iostream>

const unsigned stageNumber = 6;

class Donjon{

public:

    Donjon(unsigned, Entity&);

    Stage* getCurrentStage() const;
    std::array< std::array<char, 27>, 27> RoomCoordToChar(unsigned, unsigned);
    unsigned getStage();

    void nextStage(); // Gère la création et l'incrémentation de l'étage suivant



private:



    std::array< std::array<char, 27>, 27> placeRoomDoors(Room*, std::array< std::array<char, 27>, 27>);

    Entity hero;
    unsigned stageNb;
    unsigned stage;
    Stage *currentStage;
    unsigned seed;

};

std::ostream& operator<<(std::ostream&, const std::array< std::array<char, 27>, 27>&);

#endif