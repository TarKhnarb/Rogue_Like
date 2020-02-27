#include "Salle.h"

const unsigned maxSize = 21; // doit être un nombre impair

const unsigned minRooms = 5; // Nombre max et min de salles
const unsigned maxRooms = 15;

class Donjon{
    
public:
    
    Donjon();
    ~Donjon();
    
    void generate(); // Génère le donjon
    
    void setSeed(int);
    int getSeed();

    void setRandom(bool);
    bool getRandom();

    void countDoors();
    void doorTypeAffect(int); // Affecte a chaque salles un type en fonction de son nombre de portes (tableau)
     
private:
    
    Room* RoomsMap[maxSize][maxSize];

    int seed;
    int roomNb;

    bool random;
};
