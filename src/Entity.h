#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "Position.h"
#include "Inventory.h"
#include "Object.h"

#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <cassert>

const unsigned monsterBagSize = 3;
const unsigned playerBagSize = 10;
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
    Entity(float, float);

    /**
     * @brief construct a monster
     * @parma[in] x : position of the entity on x axis
     * @parma[in] y : position of the entity on y axis
     * @param id : the id of the monster
     */
    Entity(float, float, unsigned);

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

    const Object* getInventoryObject(unsigned) const; // Retourne un object de l'inventaire en fonction de son index

    const Object* getInventoryStuff(unsigned) const; // Retourne un object de l'equipementdu joueur

    void addInventoryObject(unsigned id, unsigned objectNb = 1); // Ajoute un object a l'inventaire en fonction de son id et du nb (par defaut à 1)
    unsigned addInventoryObjectNb(unsigned id, unsigned objectNb = 1); // // Ajoute un object a l'inventaire en fonction de son id et du nb (par defaut à 1) ET retourne le nb d'object qui n'a pas pu être ajoutés

    void removeInventoryObject(unsigned); // Vide la case de l'inventaire de l'index passé en paramètre
    unsigned removeInventoryObjectNb(unsigned id, unsigned objectNb = 1); // Enlève un object de l'inventaire avec un Id et un nombre d'éléments et retourne le nombre d'éléments manquants
	
	void swapObjects(unsigned, unsigned);

    void usePotion(unsigned);// utilise un potion en fonction de son index
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
    void moveEntity(const float&, const float&);

    void setPosition(float, float);
    int getPosition(bool) const;

    bool isItOnEntity(unsigned, unsigned);
    bool canUpgrade(std::vector<unsigned>);
    bool testIndex(unsigned);
    bool inventoryEmpty();

    std::string getName() const;
    int getMoney() const;
    int addMoney(unsigned);
    int getMaxLife() const;
    int getAttack() const;
    int getAttackSpeed() const;
    int getDefence() const;
    int getSpeed() const;

    int getLife() const;
    void removeLife(int);
    void setLife(int);

    /**
     * @brief displays the statistics of the entity
     */
    void displayEntity();


private:

    Position<float> pos;

    Inventory inventory;

    std::string name;
    unsigned money;
    Orientation orientation; //0 = North, 1 = East, 2 = South, 3 = West

    int life;
    int maxLife;
    int attack;
    int attackSpeed;
    int defence;
    int speed;
    bool fly;

};

#endif //GAME_ENTITY_H
