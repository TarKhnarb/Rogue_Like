#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H
#include <vector>
#include <string>
#include "Position.h"
#include "Random.h"
#include "Inventory.h"

class Entity {
public :
    /**
     * @brief construct a player
     * @parma[in] x : position of the entity on x axis
     * @parma[in] y : position of the entity on y axis
     * @param n : the name of the entity (player)
     */
    Entity(const unsigned &, const unsigned &, std::string);

    /**
     * @brief construct a monster
     * @parma[in] x : position of the entity on x axis
     * @parma[in] y : position of the entity on y axis
     * @param n : the name of the monster
     */
    Entity(const unsigned &, const unsigned &, unsigned const &, std::string);

    ~Entity();

    void getStatistics();
    /**
     * @brief delete an object in inventory array according to it's position in the array
     * @param[in] the index position of the object to be sold
     */
    void sellObjectByIndex(const unsigned &);
    /**
     * @brief adds an object into inventory array according to it's id
     * @param[in] the id of the object to be bought
     */
    void buyObject(const unsigned &);

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
    void moveEntity(const unsigned &, const unsigned &);

    /**
     * @brief displays the statistics of the entity
     */
    void displayEntity();


private:
    Inventory * inventory = new Inventory;
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
