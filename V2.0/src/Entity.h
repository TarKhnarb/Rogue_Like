#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "Position.h"
#include "Inventory.h"
#include "Object.h"

#include <vector>
#include <string>
#include <iostream>
#include <math.h>

const unsigned monsterBagSize = 3;
const unsigned playerBagSize = 20;
const unsigned playerStuffSize = 6;

class Entity {
public :

    enum Orientation{
        north, //0
        east , //1
        south, //2
        west , //3
    };
    
    Entity() = default;
    /**
     * @brief construct a player
     * @parma[in] x : position of the entity on x axis
     * @parma[in] y : position of the entity on y axis
     **/
    Entity(unsigned, unsigned);

    /**
     * @brief construct a monster
     * @parma[in] x : position of the entity on x axis
     * @parma[in] y : position of the entity on y axis
     * @param id : the id of the monster
     */
    Entity(unsigned&, unsigned&, unsigned);

    void getStatistics();

        // Actions sur l'inventaire de l'entity

    /**
     * @brief sell an object of the inventory array according to it's id
     * @param[in] the id of the object to be sold
     * @param[in] the number of object to sell
     */
    void sellObject(unsigned, unsigned);

    /**
     * @brief adds an object into inventory array according to it's id
     * @param[in] id : id of the object to be bought
     */
    void buyObject(unsigned, unsigned objectNb = 1);

    void equipObject(unsigned); //  equip un object en fonction de son index d'inventaire

    void unequipObject(unsigned); // deséquipe un object en fonction de son index d'equipement

    const Object* getInventoryObject(unsigned); // Retourne un object de l'inventaire en fonction de son index

    void addInventoryObject(unsigned id, unsigned objectNb = 1); // Ajoute un object a l'inventaire en fonction de son id et du nb (par defaut à 1)
    unsigned addInventoryObjectNb(unsigned id, unsigned objectNb = 1); // // Ajoute un object a l'inventaire en fonction de son id et du nb (par defaut à 1) ET retourne le nb d'object qui n'a pas pu être ajoutés

    void removeInventoryObject(unsigned); // Vide la case de l'inventaire de l'index passé en paramètre
    unsigned removeInventoryObjectNb(unsigned id, unsigned objectNb); // Enlève un object del'inventaire avec un Id et un nombre d'éléments et retourne le nombre d'éléments manquants

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

    bool isItOnEntity(unsigned, unsigned);
    bool canUpgrade(std::vector<unsigned>);
    bool testIndex(unsigned);
    bool inventoryEmpty();

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