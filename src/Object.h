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

    /**
     * @brief Get basic stats of an object
     * @return std::vector<int> Corresponding to fly, attack, attackSpeed, hp, defense, speed
     */
    std::vector<int> getStats() const;

    /**
     * @brief Get the id of the desired object
     * @return unsigned The id
     **/
    unsigned getId() const;

    /**
     * @brief Get the name of the object
     * @return std::string Containing the name
     **/
    std::string getName() const;

    /**
     * @brief Price of object
     * @return unsigned The price
     **/
    unsigned getPrice() const;

    /**
     * @brief get the resale price of the object
     * @return unsigned The resale price
     **/
    unsigned getResalePrice() const;

    /**
     * @brief Return the object type
     * @return Object::Type A enumeration of object's type
     **/
    Type getType() const;

    /**
     * @brief sets the object according to the parameter
     * @param[in] i : the object number to be set
     **/
    void setObjectNumber(unsigned);

    /**
     * @brief Add an number to object number to stack them
     * @param unsigned Number of object to add
     * @return unsigned Number of object whick cannot been added
     */
	unsigned addObjectNumber(unsigned);

    /**
     * @brief get the object number
     * @return an unsigned variable that is the object number
     **/
    unsigned getObjectNumber() const;

    /**
     * @brief get the max stack
     * @return unsigned Max stack of an object
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
