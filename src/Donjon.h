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
    unsigned getSeed();

    void setRandom(bool);
    bool getRandom();

    void setNbDoor(int);

    void countDoors();
    void doorTypeAffect(int); // Affecte a chaque salles un type en fonction de son nombre de portes (tableau)

    void affiche_donjon();
     
private:
    
    Room* RoomsMap[maxSize][maxSize];

    unsigned seed;
    int roomsNb;

    bool random;
};
