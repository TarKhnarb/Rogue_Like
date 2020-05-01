#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

const unsigned statSize = 6;
const unsigned maxIdObject = 65;

class Object {

public :
    /**
     * @brief contructs an object according to the id
     * @param[in] id :  the id of the object
     **/
	Object() = default;
    Object(unsigned);

    enum Type{
        basicStat, // 0
        helmet, // 1
        chestplate, // 2
        leggings, // 3
        boots, // 4
        projectile, // 5
        amulet, // 6
        potion, // 7
        monsterLoot // 8
    };

    std::vector<int> getStats() const;
    /**
     * @brief get the id of the desired object
     * @return the id
     **/

    unsigned getId() const;
    /**
     * @brief get the name of the object
     * @return a string containing the name
     **/
    std::string getName() const;

    /**
     * @brief price of object
     * @return the price
     **/
    unsigned getPrice() const;

    /**
     * @brief get the resale price of the object
     * @return the resale price
     **/
    unsigned getResalePrice() const;

    /**
     * @brief return the object type
     * @return ...........
     **/
    Type getType() const;

    /**
     * @brief sets the object according to the parameter
     * @param[in] i : the object number to be set
     **/
    void setObjectNumber(unsigned);

	unsigned addObjectNumber(unsigned);

    /**
     * @brief get the object number
     * @return an unsigned variable that is the object number
     **/
    unsigned getObjectNumber() const;

    /**
     * @brief get the max stack
     **/
    unsigned getMaxStack() const;

    /**
     * @brief  converts an istringstream into an unsigned variable
     * @param[in] ss : an istringstream of the current object
     * @return an unsigned variable which has been converted
     **/
    unsigned returnCsvItemSTOI(std::istringstream &);

    /**
     * @brief take an istringstream and return an string
     * @param[in] ss : istringstream
     * @return a string
     **/
    std::string returnCsvItem(std::istringstream &);

    /**
     * @brief used for debug mainly
     **/
    void display();

private:

    unsigned idObject;
    std::string name;
    unsigned price;
    unsigned resalePrice;
    Type type;
    unsigned objectNumber;

    std::vector<int> stats; // fly, attack, attackSpeed, hp, defense, speed

};


#endif //OBJECTS_H
