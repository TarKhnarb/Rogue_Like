#include "Salle.h"

const unsigned Gmax = 21;

const unsigned Smin = 5; // Nombre max et min de salles
const unsigned Smax = 15;

class Donjon{
    
public:
    
    Donjon();
    ~Donjon();
    
    void generate(); // Génère le donjon
    
    void setSeed(int);
    int getSeed();

    void setRandom(bool);
    bool getRandom();

    void affectationDoorType(int); // Affecte a chaque salles un type en fonction de son nombre de portes (tableau)
     
private:
    
    Room RoomsMap[Gmax][Gmax];

    int seed;
    int nbRoom;

    bool random;
}
