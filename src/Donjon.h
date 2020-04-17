#ifndef GAME_DONJON_H
#define GAME_DONJON_H

#include "Stage.h"
#include "Entity.h"

#include <vector>
#include <array>
#include <stdexcept>
#include <iostream>

const unsigned stageNumber = 6;

class Donjon{

public:

    Donjon(unsigned, Entity&);

    Stage* getCurrentStage() const;
    Room& getRoom(unsigned, unsigned);

    unsigned getStage();

    void nextStage(); // Gère la création et l'incrémentation de l'étage suivant

    void displayDoors(unsigned, unsigned);
    void displayMonsters(unsigned, unsigned);
    void displayRocks(unsigned, unsigned);
    void displayChest(unsigned, unsigned);

private:

    Entity hero;
    unsigned stageNb;
    unsigned stage;
    Stage *currentStage;
    unsigned seed;

};

std::ostream& operator<<(std::ostream&, const std::array< std::array<char, 27>, 27>&);

#endif