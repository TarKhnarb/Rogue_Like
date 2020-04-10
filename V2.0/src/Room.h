#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include "Door.h"
#include "Position.h"
#include "Entity.h"
#include "Chest.h"

#include <vector>

enum roomType{
    Common, // Void Room (0)
    Start, // Start with draw on the floor (1) / Aucun rocher / Aucun coffre
    CommonStart, // Start without draw on the floor (2)  / Aucun rocher / Aucun coffre
    Boss, // Salle de boss (3)  / Aucun rocher / Aucun coffre
    Room2NS1, // Room 2 Doors vertical 1 (4)   / Aucun rocher / Aucun coffre
    Room2NS2, // Room 2 Doors vertical 2 (5)   / Aucun rocher / Aucun coffre
    Room2WE1, // Room 2 Doors horizontal 1 (6) / 24 rochers   / Aucun coffre
    Room2WE2, // Room 2 Doors horizontal 2 (7) / Aucun rocher / Aucun coffre
    Room4NESW, // Room 4 Doors (8) / Aucun rocher / Aucun coffre
    Room1N, // Room 1 Door at North (9)  / 8 rochers    / 1 coffre
    Room1E, // Room 1 Door at East (10)  / Aucun rocher / 1 coffre
    Room1S, // Room 1 Door at South (11) / 16 rochers   / 1 coffre
    Room1W, // Room 1 Door at West (12)  / 31 rochers   / 1 coffre
    Room3NES, // Room 3 Doors North, East, South (13) / Aucun rocher / Aucun coffre
    Room3ESW, // Room 3 Doors East, South, West (14)  / Aucun rocher / 1 coffre
    Room3NSW, // Room 3 Doors North, South, West (15) / 11 rochers   / Aucun coffre
    Room3NEW // Room 3 Doors North, East, West (16)   / 7 rochers    / Aucun coffre
}; // Types of Rooms

struct Rock{
    bool state; // True = entier, false = cassé
    unsigned life; // Nombre de projectile avant de le detruire
    unsigned form; // forme du rocher 3 disponibles pour l'affichage sfml
    Position<float> pos; // Position dans la salle
}; // Voir comment on defini un rocher

class Room{

public:

    Room();
    Room(roomType, Entity&);
    ~Room();

    void openDoors(); // Open all Doors
    void closeDoors(); // Close all Doors (begin in a room with monsters)

    int getDoorsNb() const; // Get Door's number

    roomType getType() const; // Get Room's type
    void setType(roomType); // Set Room's type

    void placeDoor(unsigned); // Place a Door at a coordonate (0: north, 1: east, 2: south, 3: west)

    Door* getDoor(unsigned);


private:

    void fillMonsters(std::vector<unsigned>);
    void fillRocks(roomType);
    void fillChest(std::vector<unsigned>);

private:

    roomType type; // type of the current Room

    Entity hero;

    std::vector<Door*> Doors; // Index: (0: north, 1: east, 2: south, 3: west),return table of Door according their orientation
    std::vector<Entity*> monsters; // Monstres de la salle
    std::vector<Rock*> rocks; // Rochers de la salle
    std::vector<Chest*> chest; // Coffre de la salle

};

#endif
