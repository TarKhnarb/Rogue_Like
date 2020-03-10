#ifndef ROOM_H
#define ROOM_H

#include "Door.h"

enum roomType{
    Common, // Salles vides
    Start, // Start avec dessins
    CommonStart, // Start sans dessins
    Boss, // Salle de boss
}; // Types de salles

struct Rocher{
    bool etat;
}; // Voir comment on defini un rocher

class Room{

public:

    Room();
    Room(roomType);
    ~Room();

    void openDoors(); // Ouvre toutes les portes (sauf celles necessitant une clé)
    void closeDoors(); // Ferme toutes les portes (début d'une salle avec monstres)

    void unlockDoor(int); // Ouvre une porte necessite une clé et que le joueur en possède une

    int getDoorsNb() const;

    roomType getType() const;
    void setType(roomType); // Prend le seed et retourne le type de la salle en fonction du nb de portes

    void placeDoor(int);

private:

    Door* Doors[4]; // Indice: (0: nord, 1: est, 2: sud, 3: ouest), Donne le tableau des portes ne fonction de leur posistion

    roomType type; // type de la salle

};

#endif
