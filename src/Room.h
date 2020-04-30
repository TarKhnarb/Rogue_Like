#ifndef GAME_ROOM_H
#define GAME_ROOM_H


#include "Door.h"
#include "Entity.h"
#include "Chest.h"
#include "Position.h"
#include "Archetype.h"


#include <vector>

/**
 * @brief reference all type's Rooms
 */
enum roomType{
    Common, // Void Room (0)
    Start, // Start with draw on the floor (1) / Aucun rocher / Aucun coffre
    CommonStart, // Start without draw on the floor (2)  / Aucun rocher / Aucun coffre
    Boss, // Salle de boss (3)  / Aucun rocher / Aucun coffre
    Room2NS1, // Room 2 Doors vertical 1 (4)   / Aucun rocher / Aucun coffre
    Room2NS2, // Room 2 Doors vertical 2 (5)   / Aucun rocher / Aucun coffre
    Room2WE1, // Room 2 Doors horizontal 1 (6) / 24 rochers   / Aucun coffre
    Room2WE2, // Room 2 Doors horizontal 2 (7) / Aucun rocher / Aucun coffre
    Room4NESW1, // Room 4 Doors (8) / Aucun rocher / Aucun coffre
    Room4NESW2, //  Room 4 Doors (8) / Aucun rocher / Aucun coffre
    Room1N, // Room 1 Door at North (9)  / 8 rochers    / 1 coffre
    Room1E, // Room 1 Door at East (10)  / Aucun rocher / 1 coffre
    Room1S, // Room 1 Door at South (11) / 16 rochers   / 1 coffre
    Room1W, // Room 1 Door at West (12)  / 31 rochers   / 1 coffre
    Room3NES, // Room 3 Doors North, East, South (13) / Aucun rocher / Aucun coffre
    Room3ESW, // Room 3 Doors East, South, West (14)  / Aucun rocher / 1 coffre
    Room3NSW, // Room 3 Doors North, South, West (15) / 11 rochers   / Aucun coffre
    Room3NEW // Room 3 Doors North, East, West (16)   / 7 rochers    / Aucun coffre
}; // Types of Rooms
/**
 * @brief Structure for rocks
 */
struct Rock{
    /**
     * @brief construtc rocks acoording coordonates, set life at 10 and a random form
     * @param posx
     * @param posy
     */
    Rock(float posx, float posy): life (10), form (rand()%3), pos(posx, posy) {}

    /**
     * @brief Permit to check if rock is break
     * @return boolean acoording rock life != 0
     */
    bool getState() const { return life !=0; } // True = entier, false = cassé

    unsigned life; // Nombre de projectile avant de le detruire
    unsigned form; // forme du rocher, 3 disponibles pour l'affichage sfml
    Position<float> pos; // Position dans la salle

    float getPosition(bool xORy)const { return pos.getPosition(xORy);};
}; // Voir comment on defini un rocher

class Room{

public:
    /**
     * @brief construct a room aording room type and player
     * @param type of the room
     * @param entity permit to take information from player
     */
    Room(roomType, Entity*);
    ~Room();

    /**
     * @brief Open all doors of the room
     */
    void openDoors();

    /**
     * @brief Close all doors of the room
     */
    void closeDoors();

    /**
     * @brief Return door's number of the room
     * @return int between 1 and 4
     */
    int getDoorsNb() const; // Get Door's number

    /**
     * @brief Return type of the room
     * @return roomType of the room
     */
    roomType getType() const; // Get Room's type

    /**
     * @brief Set type of the room
     * @param roomType for room
     */
    void setType(roomType); // Set Room's type

    /**
     * @brief Place door according a coordonate
     * @param unsigned between 0 and 3 (0: north, 1: east, 2: south, 3: west)
     */
    void placeDoor(unsigned);

    /**
     * @brief Return a reference on room's door according a coordonate (0: north, 1: east, 2: south, 3: west)
     * @return reference on Door class
     */
    Door* getDoor(unsigned);

    /**
     * @brief Fill vector of monsters for the Boss room (1 boss/room)
     * @param unsigned corresponding to id's Monster (7 -> 10)
     */
    void fillBoss(unsigned);

    /**
     * @brief Fill vector of monster for rooms (exept CommonStart and Start) according a vector of unsigned and type of th room
     * @param std::vector<unsigned> that represent 1 to 6 ids of monsters between 2 and 6
     * @param roomType that represent type of room to fill (permit to place monsters at coordonates from Archetype.h)
     */
    void fillMonsters(std::vector<unsigned>, roomType);

    /**
     * @brief  Fill vector of rocks for room read Archetype.h to set coordonate in the room
     * @param roomType that represent type of room to fill (permit to place rocks at coordonates from Archetype.h)
     */
    void fillRocks(roomType);

    /**
     * @brief Fill chest of a room with 1 or 2 item
     * @param std::vector<undigned> that represent id of Item between 50 and 64
     */
    void fillChest(std::vector<unsigned>);

    // not const to allow HMI to change them
    /**
     * @brief Return vector of Door for the room
     * @return std::vector<Door*> Reference on Door class
     */
    std::vector<Door*> getDoors();

    /**
     * @brief Return vector of monsters for the room
     * @return std::vector<Entity*>& Reference on Entity class
     */
    std::vector<Entity*>& getMonsters();

    /**
     * @brief Return vector of rocks for the room
     * @return std::vector<Rock>& Rocks for the room
     */
    std::vector<Rock>& getRocks();

    /**
     * @brief Return a reference of chest for the room
     * @return Chest* reference on Chest class
     */
    Chest* getChest();

    /**
     * @brief  Return the sting name of roomType of the room
     * @return std::string name of the type of the room
     */
    std::string getStringType() const;

private:

    roomType type; // type of the current Room

    Entity* hero;

    std::vector<Door*> Doors; // Index: (0: north, 1: east, 2: south, 3: west),return table of Door according their orientation
    std::vector<Entity*> monsters; // Monstres de la salle
    std::vector<Rock> rocks; // Rochers de la salle
    Chest* chest; // Coffre de la salle
    
    Archetype arch;

};

#endif
