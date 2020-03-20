#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <vector>
#include <string>
#include <assert.h>
#include "sqlite3.h"

const unsigned statSize = 6;

class Object {

public :

    enum Type{
        basicStat, // 0
        projectile, // 1
        armor, // 2
        amulet, // 3
        monsterLoot // 4
    };

    Object(unsigned);
    ~Object();

    std::vector<int> getStats() const;

    unsigned getId() const;
    std::string getName() const;
    unsigned getPrice() const;
    unsigned getResalePrice() const;
    Type getObjectType() const;
    unsigned getObjectNumber() const;
    const unsigned getMaxStack() const;

    void display();

private:

    unsigned idObject;
    std::string name;
    unsigned price;
    unsigned resalePrice;
    Type type;
    unsigned objectNumber;

    std::vector<int> stats; // fly, attack, attackSpeed, hp, defense, speed

};


#endif //GAME_OBJECTS_H
