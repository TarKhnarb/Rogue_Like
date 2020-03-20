#ifndef GAME_INVENTORY_H
#define GAME_INVENTORY_H

#include "Objects.h"
#include <vector>
#include <array>

class Inventory {

public:

    Inventory() = default; // par defaut pour les besoin des inventaires de différentes tailles

    /**
     * @brief adds an object by default id = 1 to array inventory
     */
    Inventory(const unsigned);

    /**
     * @brief destructor for Inventory
     */
    ~Inventory();
    
    /**
     * @brief displays inventory Objects statistics and a resume of all combined statistics
     */
    void displayInventory();

    void displayEquipment();

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

    std::vector<int> getAllStats() const; // entityFly, entityAttack, entityAttackSpeed, entityHp, entityDefense, entitySpeed


    std::vector<unsigned> getObjectStats(const unsigned) const;



private :
    std::array<Object *> inventory; // 0 : Stats de base

};


#endif //GAME_INVENTORY_H
