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

    /**
     * @bried Construct Donjon according stage number, entity for player informations
     */
    Donjon(unsigned, Entity*);
	~Donjon();

	/**
	 * @brief Return reference on the current room genrate in the donjon
	 * @return Stage* Reference on Stage class
	 */
    Stage* getCurrentStage() const;

    /**
     * @brief Return reference on a room of the current stage according coordonate in C 2D Array
     * @param unsigned i coordonate in array
     * @param unsigned j coordonate in array
     * @return Room* Reference on Room class
     */
    Room* getRoom(unsigned, unsigned);

    /**
     * @brief
     * @return
     */
    unsigned getStage();

    /**
     * @brief Clean current stage and generate the next stage
     */
    void nextStage(); // Gère la création et l'incrémentation de l'étage suivant

    /**
     * @brief Display in terminal different informations of element which composed the room according corrdonates in C 2D Array
     * @param unsigned i coordonate of the Array
     * @param unsigned j coordonate of the Array
     */
    void displayDoors(unsigned, unsigned);
    void displayMonsters(unsigned, unsigned);
    void displayRocks(unsigned, unsigned);
    void displayChest(unsigned, unsigned);

private:

    Entity* hero;
    unsigned stageNb;
    unsigned stage;
    Stage *currentStage;
    unsigned seed;

};

std::ostream& operator<<(std::ostream&, const std::array< std::array<char, 27>, 27>&);

#endif
