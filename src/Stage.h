#ifndef STAGE_H
#define STAGE_H

#include <iostream>

#include "Room.h"

const unsigned maxSize = 21; // doit être un nombre impair

const unsigned minRooms = 10; // Nombre max et min de salles
const unsigned maxRooms = 20;

class Stage{
    
public:
    
    Stage();
    ~Stage();

    void generate(unsigned &); // Génère le Stage
    
    void setSeed(unsigned);
    unsigned getSeed() const;

    void setRandom(bool);
    bool getRandom() const;

    Room* getRoom(unsigned, unsigned) const;

    void placeDoors();
    void affectRoomTypeMonsterObject(); // Affecte a chaque salles un type en fonction de son nombre de portes (tableau)

    void reset(unsigned);

    bool countRoomsAround(unsigned, unsigned);
     
private:
    
    Room* RoomsMap[maxSize][maxSize];

    unsigned seed;
    unsigned roomsNb;

    bool random;
};

std::ostream& operator<<(std::ostream&, const Stage&);

#endif
