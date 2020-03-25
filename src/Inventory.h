#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Object.h"


const unsigned maxIndexBasicStatInventory = 2; // => [1] = basic stat
const unsigned maxIndexEquipmentInventory = 4; // => [2 -> 4] = equipment

class Inventory {

public:
    Inventory() = default; // par defaut pour les besoin des inventaires de différentes tailles


    Inventory(unsigned, unsigned);

    ~Inventory();

    bool testSameType(unsigned, Object::Type); // Test si l'id de l'object selectionné est du même type
    bool testFullObjectInventory();
    bool testFullStack(unsigned); // Test si l'object a atteint son stack max
    bool testObjectExist(unsigned); // return si inventory[index] ou non
    int numberAddStack(unsigned, unsigned); // Test si l'idObject existe et return le nombre d'object encore ajoutable

    void addRecursiveObjectId(unsigned, unsigned, unsigned, bool &, unsigned &); // id, objNum, startIndex, done, objAdd


    void addObjectId(unsigned, unsigned, unsigned &);

    void addObjectIndex(unsigned, unsigned, unsigned, unsigned &);

    void removeObjectIndex(unsigned, unsigned);

    void deleteObjectIndex(unsigned);

    void deleteObjectId(unsigned);

    void moveInventoryObject(unsigned, unsigned); // deplace un object entre deux cases avec leurs index si la case est occupé echange les deux objects

    void equipObjectIndex(unsigned); // equip l'équipement en fonction de son type si un equipé le remplace
    void unequipObjectIndex(unsigned, unsigned &); // unequip


    std::vector<int> getAllEntityStats() const; // entityFly, entityAttack, entityAttackSpeed, entityHp, entityDefense, entitySpeed
    std::vector<int> getObjectStats(unsigned) const;
    std::string getObjectName(unsigned) const;
    unsigned getObjectResalePrice(unsigned) const;
    unsigned getObjectNumber(unsigned) const;


    void displayBasicStat();

    void displayInventory();

    void displayEquipment();

private :
    std::vector<Object*> inventory; // 0 : Stats de base | 1 -> 4 : equipement | 4 -> inventory.size() : inventaire
    bool full;
};

#endif