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
    std::string getName() const;
    std::vector<unsigned > getStats() const; //

    void display();

protected :
    unsigned idObject;
    std::string name;
    unsigned price;
    unsigned resalePrice;
    bool jump;
    std::vector<unsigned> stats; //attack, defense, speed
};


#endif //GAME_OBJECTS_H
