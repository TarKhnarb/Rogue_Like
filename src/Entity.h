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
    
    /**
     * @brief equips an object
     * @param[in] : the unsigned value of the object to be equiped
     */
    void equipObject(unsigned);
    
    /**
     * @brief de-equips an object
     * @param[in] : the unsigned value of the object to be de-equiped
     */
    void unequipObject(unsigned); 
    
    /**
     * @return an object according to index of inventory
     * @param[in] : the index of the inventory to be returned
     */ 
    const Object* getInventoryObject(unsigned) const;
    
    /**
     * @return an object equipement according to index of inventory
     * @param[in] : the index of the inventory to be returned
     */ 
    const Object* getInventoryStuff(unsigned) const;

    /**
     * @brief add object to inventory
     * @param[in] : the object id to be added
     * @param[in] : the number of object to be added
     */ 
    void addInventoryObject(unsigned id, unsigned objectNb = 1);
    
    /**
     * @brief add object to inventory
     * @param[in] : the object id to be added
     * @param[in] : the number of object to be added
     * @return : the number of object not added if problem
     */ 
    unsigned addInventoryObjectNb(unsigned id, unsigned objectNb = 1);

    /**
     * @brief empties the inventory cell of array 
     * @param[in] : the index of the cell to be emptied
     */ 
    void removeInventoryObject(unsigned); 
    
    /**
     * @brief empties the inventory cell of array 
     * @param[in] : the index of the cell to be emptied
     * @return the number of object that could not be taken away
     */ 
    unsigned removeInventoryObjectNb(unsigned id, unsigned objectNb = 1);
	
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

    /**
     * @brief set position entity according to x ad y
    */
    
    void setPosition(float, float);
    /**
        * @brief get position entity according to x ad y
    */
    int getPosition(bool) const;

    
    bool isItOnEntity(unsigned, unsigned);
    
    /**
     * @brief return true if entity can upgrade
     */
    bool canUpgrade(std::vector<unsigned>);
    
    /**
     * @brief test if there is object at that index
     */ 
    bool testIndex(unsigned);
    
    /**
     * @brief return true if inventory is empty
     */ 
    bool inventoryEmpty();

    /**
     * @brief get name of entity
     */
    std::string getName() const;
    
    /**
     * @return money available to entity
     */ 
    int getMoney() const;
    
    /**
     * @brief add certain amount of money to entity according to the unsigned value in parameter
     */
    int addMoney(unsigned);
    
    /**
     * @brief get the life of entity
     */ 
    int getMaxLife() const;
    
    /**
     * @brief get the attck of entity
     */ 
    int getAttack() const;
    
    /**
     * @brief get attack speed of entity
     */ 
    int getAttackSpeed() const;
    
    /**
     * @brief get defence 
     */ 
    int getDefence() const;
    
    /**
     * @brief get speed
     */ 
    int getSpeed() const;

    
    unsigned getEntityId() const;

    bool getState() const;
    
    /**
     * @brief get life
    */
    int getLife() const;
    
    /**
     * @brief remove life when called to entity
     */ 
    void removeLife(int);
    
    /**
     * @brief gives life from parameter when called
     */ 
    void setLife(int);
    
    /**
     * @brief set max life to entity
     */ 
    void setMaxLife(int);

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
