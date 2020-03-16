#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Position.h"


class Etity {
public:
    unsigned getMoney() const;
    void setMoney(unsigned);
    bool canJump() const;
    unsigned getStatistics(unsigned) const;

private:
   // Position position;
    //Inventory inventory;
    unsigned money;
    bool jump;
    std::string name;
};
#endif