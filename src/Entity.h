#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <iostream>
#include <math.h>

#include "Position.h"
#include "Inventory.h"

const unsigned monsterBagSize = 3;
const unsigned playerBagSize = 20;
const unsigned playerStuffSize = 3;

class Entity {
public :

    enum Orientation{
        north, //0
        south, //1
        east , //2
        west , //3
    };
    
    Entity() = default;
    /**
     * @brief construct a player
     * @parma[in] x : position of the entity on x axis
     * @parma[in] y : position of the entity on y axis
     **/
    Entity(unsigned&, unsigned&);

    /**
     * @brief construct a monster
     * @parma[in] x : position of the entity on x axis
     * @parma[in] y : position of the entity on y axis
     * @param id : the id of the monster
     */
    Entity(unsigned&, unsigned&, unsigned);


    void getStatistics();
    /**
     * @brief delete an object in inventory array according to it's object id
     * @param[in] the id of the object to be sold
     * @param[in] the number of object to sell
     */
    void sellObject(unsigned, unsigned);
    /**
     * @brief adds an object into inventory array according to it's id
     * @param[in] id : id of the object to be bought
     */
    void buyObject(unsigned, unsigned objectNb = 1);

    void equipObject(unsigned);

    void unequipObject(unsigned);

    /**
    * @brief check if player can fly
    * @return a bool : 1 if player can fly >> 0 if not
    */
    bool entityCanFly() const;
    
    /**
     * @brief get orientation of player
     * @return an unsigned variable according to the orientation of the entity
     */
    unsigned getOrientation()const;

    /**
     * @brief moves the entity according to parameters, and change orientation of player
     * @param[in] x : value which represent the number to move the entity on the x axis
     * @param[in] y : value which represent the number to move the entity on the y axis
     */
    void moveEntity(const int&, const int&);

    void setPosition(int, int);
    int getPosition(bool) const;

    /**
     * @brief displays the statistics of the entity
     */
    void displayEntity();

private:

    Position<int> pos;

    Inventory inventory;

    std::string name;
    unsigned money;
    Orientation orientation; //0 = North, 1 = East, 2 = South, 3 = West

    unsigned life;
    unsigned attack;
    unsigned attackSpeed;
    unsigned defence;
    unsigned speed;
    bool fly;

};


#endif //GAME_ENTITY_H
