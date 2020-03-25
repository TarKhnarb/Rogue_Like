#ifndef SRC_MENU_H
#define SRC_MENU_H
#include <string>

class menu {
public :

    void displayBounds();
    void rules();

    void showPlayer(); //init entity inside >> display entity

    void showDB();
    unsigned returnCsvItemSTOI(std::istringstream & ss);
    std::string returnCsvItem(std::istringstream & ss);

    unsigned logicPlayer(); //return choice unsigned

//    buyObject(); //recuperation entity(inventory)
  //  sellObject(); //same
/*
    switch(){
        checkEntityAction();
        goToGame(); >> call game.cpp/h
    }
*/
private :
    unsigned choice;
    unsigned console_size = 100;
    unsigned nb_object = 8;
};


#endif //SRC_MENU_H
