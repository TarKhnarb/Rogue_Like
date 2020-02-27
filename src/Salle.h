const unsigned NbType = 14;

class Door{     // Savoir si la porte existe ou pas, si elle necessite une clé ou un etage clear, 0 nord, 1 est, 2 sud, 3 ouest
public:

    Door();
    ~Door();

    void openIt();

private:

    bool exist;
    bool key;
    bool open;
};



enum TypeRoom{
    Start;
    Start
}; // Types de salles

class Rooms{

public:

    Rooms();
    ~Rooms();

    void openDoors(); // ouvre toutes les portes;
    void countDoors();

    void getType();
    void setType(int); // prend le seed et retourne le type de la salle en fonction du nb de portes

private:

    int nbDoor; // Nombre de porte(s) dans la salle

    Door Doors[4]; // indice: (0: nord, 1: est, 2: sud, 3: ouest), Donne le tableau des portes ne fonction de leur posistion

    TypeRoom type;
};