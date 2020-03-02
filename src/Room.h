#include "Door.h"

enum roomType{
    None,
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


    void setDoorsNb(int); // Set la valeur du nobre de portes de la salle
    int getDoorsNb();

    int getType();
    void setType(roomType); // Prend le seed et retourne le type de la salle en fonction du nb de portes

    void setDoorExist(int, bool);

private:

    int doorsNb; // Nombre de porte(s) dans la salle

    Door* Doors[4]; // Indice: (0: nord, 1: est, 2: sud, 3: ouest), Donne le tableau des portes ne fonction de leur posistion

    roomType type; // type de la salle

};