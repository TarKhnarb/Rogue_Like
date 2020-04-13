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
    
    Stage(Entity &);
    ~Stage();

    void generate(unsigned &); // Génère le Stage
    
    void setSeed(unsigned);
    unsigned getSeed() const;

    void setRandom(bool);
    bool getRandom() const;

    Room* getRoom(unsigned, unsigned) const;

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

    Entity hero;
    
    Room* RoomsMap[maxSize][maxSize];

    unsigned seed;
    unsigned roomsNb;

    bool random;
};

std::ostream& operator<<(std::ostream&, const Stage*);

#endif
