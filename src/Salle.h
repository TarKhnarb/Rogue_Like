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
    Common;
    Start;
    End;
}; // Types de salles

class Room{

public:

    Room();
    ~Room();

    void openDoors(); // Ouvre toutes les portes
    void setDoorsNb(int); // Set la valeur du nobre de portes de la salle

    void getType();
    void setType(int); // Prend le seed et retourne le type de la salle en fonction du nb de portes

private:

    int doorsNb; // Nombre de porte(s) dans la salle

    Door Door[4]; // Indice: (0: nord, 1: est, 2: sud, 3: ouest), Donne le tableau des portes ne fonction de leur posistion

    roomType type;
};
