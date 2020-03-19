#ifndef GAME_INVENTORY_H
#define GAME_INVENTORY_H

#include "Objects.h"
#include <vector>


class Inventory {
public:
    /**
     * @brief adds an object by default id = 1 to array inventory
     */
    Inventory();
    /**
     * @brief destructor for Inventory
     */
    ~Inventory();
    
    /**
     * @brief displays inventory Objects statistics and a resume of all combined statistics
     */
    void displayInventory();

     /**
      * @brief add an Object into Inventory according to it's id
      * @param[in] an unsigned variable that corresponds to the Object id to add
      */
    void addObject(const unsigned &);
    /**
     * @brief remove object according to array index
     * @param[in] the index of the Object in array inventory which has to be removed
     */
    void removeObjectIndex(const unsigned &);
    /**
    * @brief remove object according to it's id
    * @param[in] the id of the Object in array inventory which has to be removed
    */
    void removeObjectId(const unsigned &);
    /**
    * @brief calculates the sum of all objects statistics
    */
    void calculateStatistics();

    bool getFly() const;
    unsigned getAttack() const;
    unsigned getAttackSpeed() const;
    unsigned getHp() const;
    unsigned getDefence() const;
    unsigned getSpeed() const;

    unsigned getResalePrice(const unsigned) const;
    unsigned getPrice(const unsigned) const;

private :
    std::vector<Object> inventory;
    unsigned inventorySize=5;//array size limit inventory

    //inventory statistics
    bool fly;
    unsigned hp;
    unsigned attack;
    unsigned attackSpeed;
    unsigned defence;
    unsigned speed;
};


#endif //GAME_INVENTORY_H
