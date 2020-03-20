#ifndef GAME_INVENTORY_H
#define GAME_INVENTORY_H

#include "Objects.h"
#include <vector>

const unsigned maxIndexBasicStatInventory = 1; // => [0] = basic stat
const unsigned maxIndexEquipmentInventory = 4; // => [1 -> 4] = equipment

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

    bool testSameType(const unsigned, Object::Type); // Test si l'id de l'object selectionné est du même type
    bool testFullObjectInventory();
    
    /**
     * @brief displays inventory Objects statistics and a resume of all combined statistics
     */
    void displayInventory();

    void displayEquipment();

     /**
      * @brief add an Object into Inventory according to it's id
      * @param[in] an unsigned variable that corresponds to the Object id to add
      */
    void addObjectId(const unsigned &);

    /**
     * @brief delete object according to array index
     * @param[in] the index of the Object in array inventory which has to be removed
     */
    void deleteObjectIndex(const unsigned &);

    /**
    * @brief delete object according to it's id
    * @param[in] the id of the Object in array inventory which has to be removed
    */
    void deleteObjectId(const unsigned &);

    void moveInventoryObject(const unsigned &, const unsigned &); // deplace un object entre deux cases avec leurs index si la case est occupé echange les deux objects

    void equipObjectIndex(const unsigned &); // equip l'équipement en fonction de son type si un equipé le remplace
    void unequipObjectIndex(const unsigned &); // unequip

    /**
    * @brief calculates the sum of all objects statistics
    */

    std::vector<int> getAllStats() const; // entityFly, entityAttack, entityAttackSpeed, entityHp, entityDefense, entitySpeed


    std::vector<unsigned> getObjectStats(const unsigned) const;



private :
    std::vector<Object *> inventory; // 0 : Stats de base | 1 -> 4 : equipement | 4 -> inventory.size() : inventaire

};


#endif //GAME_INVENTORY_H
