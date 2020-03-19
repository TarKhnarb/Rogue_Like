#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H


#include <vector>
#include <string>
#include "sqlite3.h"

const unsigned statSize = 5;

class Object {
public :
    Object();
    Object(unsigned);
    ~Object();

    unsigned getId() const;
    std::string getName() const;
    unsigned getPrice() const;
    unsigned getResalePrice() const;
    bool getFly();

    unsigned getAttack() const;
    unsigned getAttackSpeed() const;
    unsigned getHp() const;
    unsigned getDefence() const;
    unsigned getSpeed() const ;

    std::vector<unsigned > getStats() const;

    void display();

protected :
    unsigned idObject;
    std::string name;
    unsigned price;
    unsigned resalePrice;
    bool fly;

    std::vector<unsigned> stats; //attack, attackSpeed, hp, defense, speed

};


#endif //GAME_OBJECTS_H
