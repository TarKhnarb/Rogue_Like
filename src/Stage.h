#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Room.h"
#include "Entity.h"

const unsigned maxSize = 21; // doit être un nombre impair

const unsigned minRooms = 10; // Nombre max et min de salles
const unsigned maxRooms = 20;

class Stage{
    
public:

    /**
     * @brief Construct a stage according the player
     * @param Entity* Reference to Entity class
     */
    Stage(Entity*);
    ~Stage();

    /**
     * @brief Generate a stage of Room in a C 2D Array according stage number
     * @param unsigned& Stage number
     */
    void generate(unsigned &); // Génère le Stage

    /**
     * @brief Set the seed for the stage generation
     * @param unsigned Reference to new seed
     */
    void setSeed(unsigned);

    /**
     * @brief Return the seed of the stage
     * @return unsigned Corresponding to stage's seed
     */
    unsigned getSeed() const;

    /**
     * @brief Set Random for the seed if it isn't set before gernerate
     * @param bool True or False
     */
    void setRandom(bool);

    /**
     * @brief Get the boolean of random set
     * @return bool if random has been set
     */
    bool getRandom() const;

    /**
     * @brief Return Reference on a Room according its coordonates in C 2D Array
     * @param unsigned i coordonate of the Array
     * @param unsigned j coordonate of the Array
     * @return Room* Reference to Room class
     */
    Room* getRoom(unsigned, unsigned);

    /**
     * @brief Affectect at each room of the stage a type depending Room's number and position; monsters, chest and rocks depending type of room
     */
    void affectRoomTypeMonsterObject(); // Affecte a chaque salles un type en fonction de son nombre de portes (tableau)

private:
    void placeDoors();

    void reset(unsigned);

    bool countRoomsAround(unsigned, unsigned);

    std::vector<unsigned> randomMonsters(); // return a vector of X ids to fill monsters in the room
    std::vector<unsigned> randomObjects(unsigned); // return a vector of X ids to fill chest of the room
    unsigned randomObjectWithProbability(); // return (1) or (2) with the probability of 1/3 for (2)

public:
    std::vector<Door*> getDoors(unsigned, unsigned) const;
    std::vector<Entity*> getMonsters(unsigned, unsigned) const;
    std::vector<Rock> getRocks(unsigned, unsigned) const;
    Chest* getChest(unsigned, unsigned) const;

private:

    Entity* hero;
    
    Room* RoomsMap[maxSize][maxSize];

    unsigned seed;
    unsigned roomsNb;

    bool random;
};

std::ostream& operator<<(std::ostream&, Stage*);

#endif
