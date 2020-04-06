#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include "Door.h"
#include "Position.h"
#include <vector>

enum roomType{
    Common, // Void Room (0)
    Start, // Start with draw on the floor (1)
    CommonStart, // Start without draw on the floor (2)
    Boss, // Salle de boss (3)
    Object, // Room Boost Object (4)
    Room2NS1, // Room 2 Doors vertical 1 (5)
    Room2NS2, // Room 2 Doors vertical 2 (6)
    Room2WE1, // Room 2 Doors horizontal 1 (7)
    Room2WE2, // Room 2 Doors horizontal 2 (8)
    Room4NESW, // Room 4 Doors (9)
    Room1N, // Room 1 Door at North (10)
    Room1E, // Room 1 Door at East (11)
    Room1S, // Room 1 Door at South (12)
    Room1W, // Room 1 Door at West (13)
    Room3NES, // Room 3 Doors North, East, South (14)
    Room3ESW, // Room 3 Doors East, South, West (15)
    Room3NSW, // Room 3 Doors North, South, West (16)
    Room3NEW // Room 3 Doors North, East, West (17)
}; // Types of Rooms

struct Rock{
    bool state; // True = entier, false = cassé
    unsigned life; // Nombre de projectile avant de le detruire
    unsigned form; // forme du rocher 3 disponibles pour l'affichage sfml
    Position<unsigned> pos; // Position dans la salle
}; // Voir comment on defini un rocher

class Room{

public:

    Room();
    Room(roomType, unsigned rockNb = 0);
    ~Room();

    void openDoors(); // Open all Doors
    void closeDoors(); // Close all Doors (begin in a room with monsters)

    void unlockDoor(int); // Unlock a Door if it need a key and player has any

    int getDoorsNb() const; // Get Door's number

    roomType getType() const; // Get Room's type
    void setType(roomType); // Set Room's type

    void placeDoor(unsigned); // Place a Door at a coordonate (0: north, 1: east, 2: south, 3: west)

    Door* getDoor(unsigned);

private:

    Door* Doors[4]; // Index: (0: north, 1: east, 2: south, 3: west),return table of Door according their orientation

    roomType type; // type of the current Room

    std::vector<Rock*> rocks;

};

#endif
