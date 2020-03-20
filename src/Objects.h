#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H


#include <vector>
#include <string>
#include <assert.h>
#include "sqlite3.h"

const unsigned statSize = 6;

class Object {

public :
    Object(unsigned);
    ~Object();

    std::vector<int> getStats() const;

    unsigned getId() const;
    std::string getName() const;
    unsigned getPrice() const;
    unsigned getResalePrice() const;

    void display();

private:

    unsigned idObject;
    std::string name;
    unsigned price;
    unsigned resalePrice;

    std::vector<int> stats; // fly, attack, attackSpeed, hp, defense, speed

};


#endif //GAME_OBJECTS_H
