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
    /**
     * @brief Place doors in the stage depending on placed rooms
     */
    void placeDoors();

    /**
     * @brief Used to reset the stage if we cannot generate it correctly
     * @param unsigned Represent the lvl of the stage in the donjon
     */
    void reset(unsigned);

    /**
     * @brief Counts the doors of a room and returns true only if there is only one door
     * @return boolean if only one door in the room
     */
    bool countRoomsAround(unsigned, unsigned);

    /**
     * @brief Fill monsters in a room with random on number and id
     * @return std::vector<unsigned> of monster's Id to fill a room
     */
    std::vector<unsigned> randomMonsters(); // return a vector of X ids to fill monsters in the room

    /**
     * @brief Fill object of a chest in a room with random on number and id
     * @param unsigned Object number to fill
     * @return std::vector<unsigned> of object's Id to fill a chest
     */
    std::vector<unsigned> randomObjects(unsigned); // return a vector of X ids to fill chest of the room

    /**
     * @brief return (1) or (2) with the probability of 1/3 for (2) to select object number
     * @return unsigned 1 or 2
     */
    unsigned randomObjectWithProbability(); // return (1) or (2) with the probability of 1/3 for (2)

public:
    /**
     * @brief Return doors vector of a room according its coordonate
     * @param unsigned Coordonate i of the stage room
     * @param unsigned Coordonate j of the stage room
     * @return std::vector<Door*> A reference on room's doors, Door class
     */
    std::vector<Door*> getDoors(unsigned, unsigned) const;

    /**
     * @brief Return monsters vector of a room according its coordonate
     * @param unsigned Coordonate i of the stage room
     * @param unsigned Coordonate j of the stage room
     * @return std::vector<Entity*> A reference on room's monsters, Entity class
     */
    std::vector<Entity*> getMonsters(unsigned, unsigned) const;

    /**
     * @brief Return rocks vector of a room according its coordonate
     * @param unsigned Coordonate i of the stage room
     * @param unsigned Coordonate j of the stage room
     * @return std::vector<Rock> Rocks of the room, Rock structure
     */
    std::vector<Rock> getRocks(unsigned, unsigned) const;

    /**
     * @brief Return chest reference of a room according its coordonate
     * @param unsigned Coordonate i of the stage room
     * @param unsigned Coordonate j of the stage room
     * @return Chest* Reference on Chest class
     */
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
