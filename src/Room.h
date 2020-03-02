#ifndef ROOM_H
#define ROOM_H

#include "Door.h"

enum roomType{
    Common,
    Start,
    End,
}; // Types de salles

class Room{

public:

    Room();
    ~Room();

    void openDoors(); // Ouvre toutes les portes (sauf celles necessitant une clé)
    void closeDoors(); // Ferme toutes les portes (début d'une salle avec monstres)

    void unlockDoor(Door); // Ouvre une porte necessite une clé et que le joueur en possède une

    int getDoorsNb() const;

    roomType getType() const;
    void setType(roomType); // Prend le seed et retourne le type de la salle en fonction du nb de portes

    void placeDoor(int);

private:

    Door* Doors[4]; // Indice: (0: nord, 1: est, 2: sud, 3: ouest), Donne le tableau des portes ne fonction de leur posistion

    roomType type; // type de la salle

};

#endif
