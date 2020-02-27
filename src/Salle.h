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



enum roomType{
    Start;
    End;
}; // Types de salles

class Room{

public:

    Rooms();
    ~Rooms();

    void openDoors(); // ouvre toutes les portes;
    void countDoors();

    void getType();
    void setType(int); // prend le seed et retourne le type de la salle en fonction du nb de portes

private:

    int nbDoors; // Nombre de porte(s) dans la salle

    Door Door[4]; // indice: (0: nord, 1: est, 2: sud, 3: ouest), Donne le tableau des portes ne fonction de leur posistion

    roomType type;
};
