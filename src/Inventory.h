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

private :
    std::vector<Objects> inventory;
    unsigned inventorySize=5;//array size limit inventory

    //inventory statistics
    bool jump;
    unsigned attack;
    unsigned defence;
    unsigned speed;
};


#endif //GAME_INVENTORY_H
