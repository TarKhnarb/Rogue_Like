#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
#include <string>

const unsigned statSize = 6;

class Object {

public :

    enum Type{
        basicStat, // 0
        projectile, // 1
        armor, // 2
        amulet, // 3
        monsterLoot // 4
    };
    /**
     * @brief contructs an object according to the id 
     * @param[in] id :  the id of the object
     **/
    Object(unsigned);
    
    /**
     * @brief destructor
     **/
    ~Object();

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
    Type getObjectType() const;
    
    /**
     * @brief sets the object according to the parameter
     * @param[in] i : the object number to be set
     **/
    void setObjectNumber(unsigned);
    
    /**
     * @brief get the object number
     * @return an unsigned variable that is the object number
     **/
    unsigned getObjectNumber() const;
    
    /**
     * @brief get the max stack 
     **/
    const unsigned getMaxStack() const;
    
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


#endif //GAME_OBJECTS_H
