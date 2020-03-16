#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H


#include <vector>
#include <string>
#include <sqlite3.h>

class Object {
public :
    Object();
    Object(unsigned);
    ~Object();

    unsigned getId() const;
    unsigned getPrice() const;
    unsigned getResalePrice() const;
    bool getJump() const;

    unsigned getAttack(); // a traiter dans le constructeur voir si on n'y rajoute pas à la base directement vu qu'on a un base de données
    unsigned getDefence();
    unsigned getSpeed();

    std::string getName() const;
    //std::vector<unsigned > getStats() const; //

    void display();

protected :
    unsigned idObject;
    std::string name;
    unsigned price;
    unsigned resalePrice;
    bool jump;

    unsigned attack; // Anciennement vector
    unsigned defence;
    unsigned speed;

    //std::vector<unsigned> stats; //attack, defense, speed
};


#endif //GAME_OBJECTS_H
