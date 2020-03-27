#ifndef SRC_MENU_H
#define SRC_MENU_H
#include <string>

class menu {
public :

    /**
     * @brief controls the whole menu, all functions are included inside that procedure
     * @brief allows player to chose from 4 option, player stats,buy and sell object , go to game
    */
    void logic(); 

    /**
     * @brief the bounds of the menu with a string to make it visually appealing
    */
    void displayBounds();
    
    /**
     * @brief displays the rules fothe menu, what the player can and not do
    */ 
    void rules();
    
    /**
     * @brief is r included multiple times in the code, shortened version of the menu rules
    */
    void sub_rules();
    
    /**
     * @brief show the player stats, the player is init here with all his parameters 
     */ 
    void showPlayer(); //(waiting for entity to be finsihed,can't display stats if not)
    
    /**
     * @brief show the object from csv file thta the player can buy from
     * /
    void showDB();
    
    /**
     * @brief  converts an istringstream into an unsigned variable
     * @param[in] ss : an istringstream of the current object
     * @return an unsigned variable which has been converted
     */
    unsigned returnCsvItemSTOI(std::istringstream & ss);
    
    /**
     * @brief take an istringstream and return an string
     * @param[in] ss : istringstream
     * @return a string
     */
    std::string returnCsvItem(std::istringstream & ss);

    /**
     * @brief gets input from keyboard, checks if valid
     * @return the chosen input from player
     * /
    unsigned logicPlayer(const unsigned &); //return choice unsigned

    /**
     * @brief allows a player to buy an object according to his inventory and what is available in csv file
     * / 
    void buyObject(); //recuperation entity(inventory) //can't work if entity is not complete
    
    /**
     * @brief allows a player to sell an object from his inventory 
     * /
    void sellObject();  //recuperation entity(inventory) //can't work if entity is not complete

private :
    unsigned choice;
    unsigned console_size = 100;
    unsigned nb_object = 8;
};


#endif //SRC_MENU_H
