#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <vector>
#include <string>
#include <iostream>

#include "Position.h"
#include "Inventory.h"

const unsigned monsterBagSize = 3;
const unsigned playerBagSize = 20;
const unsigned playerStuffSize = 3;

class Entity {
public :
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

    ~Entity();

    void getStatistics();
    /**
     * @brief delete an object in inventory array according to it's position in the array
     * @param[in] the index position of the object to be sold
     */
    void sellObjectByIndex(unsigned, unsigned);
    /**
     * @brief adds an object into inventory array according to it's id
     * @param[in] id : id of the object to be bought
     */
    void buyObject(unsigned, unsigned objectNb = 1);

    /**
    * @brief check if player can fly
    * @return a bool : 1 if player can fly >> 0 if not
    */
    bool entityCanFly() const;

    /**
     * @brief moves the entity according to parameters
     * @param[in] x : value which represent the number to move the entity on the x axis
     * @param[in] y : value which represent the number to move the entity on the y axis
     */
    void moveEntity(const unsigned&, const unsigned&);

    /**
     * @brief displays the statistics of the entity
     */
    void displayEntity();


private:
    Inventory inventory;
    Position<int> * pos;

    std::string name;
    unsigned money;
    unsigned life;
    unsigned attack;
    unsigned attackSpeed;
    unsigned defence;
    unsigned speed;
    bool fly;

};


#endif //GAME_ENTITY_H
