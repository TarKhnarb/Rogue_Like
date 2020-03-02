#ifndef DONJON_H
#define DONJON_H

#include <iostream>

#include "Room.h"

const unsigned maxSize = 21; // doit être un nombre impair

const unsigned minRooms = 5; // Nombre max et min de salles
const unsigned maxRooms = 15;

class Donjon{
    
public:
    
    Donjon();
    ~Donjon();
    
    void generate(); // Génère le donjon
    
    void setSeed(unsigned);
    unsigned getSeed() const;

    void setRandom(bool);
    bool getRandom() const;

    unsigned getSize() const;
    Room* getRoom(unsigned, unsigned) const;

    void placeDoors();
    void roomTypeAffect(); // Affecte a chaque salles un type en fonction de son nombre de portes (tableau)
     
private:
    
    Room* RoomsMap[maxSize][maxSize];

    unsigned seed;
    int roomsNb;

    bool random;
};

std::ostream& operator<<(std::ostream&, const Donjon&);

#endif
