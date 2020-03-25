#include "menu.h"
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>


std::string spacingV1(100/2, ' ');
std::string spacingV2(40, ' ');
std::string spacingV3(50/4, ' ');

void menu::displayBounds() {
    for(unsigned i=0;i<console_size;++i){
        std::cout<<"-";
    }
    std::cout<<std::endl;
}

void menu::rules(){
    displayBounds();
    std::cout<< spacingV1 << "Hello"<<std::endl;
    std::cout<< spacingV2 << "This is the main menu game"<<std::endl;
    std::cout<<std::endl;
    std::cout<< spacingV2 << "Please type in the console what you want to do" <<std::endl;
    std::cout<<std::endl;
    std::cout<< spacingV3 << "- One(1) to buy an object" << std::endl;
    std::cout<< spacingV3 << "- two(2) to sell and object of your player inventory" <<std::endl;
    std::cout<< spacingV3 << "- Three(3) to go to the game with your current inventory and play against monstrers" <<std::endl;
    std::cout<<std::endl;
    std::cout<< spacingV3 << "Other inputs will not be taken into account" << std::endl;
    std::cout<<std::endl;
    displayBounds();
}

void menu::showPlayer() {
    //init player basic
    //display player stats
}

void menu::showDB() {
    //showing the csv file
    std::ifstream file;
    file.open("Objects.csv"); //verify path >> makefile

    if (file.is_open()) {

        std::string csvItem;

        std::cout << "Here are the stats of the objects you can buy : " << std::endl;
        std::cout << std::endl;
        std::cout << "id, price, resalePrice, fly, attack, attackSpeed, hp, defence, speed, type, name" << std::endl;
        std::cout << std::endl;

        for (unsigned i = 0; i < 6; ++i) { //display stats objects from csv file
            getline(file, csvItem); //line n°'i'
            std::istringstream iss(csvItem);
            //id,price
            std::cout << returnCsvItemSTOI(iss) << "    ,    " << returnCsvItemSTOI(iss);
            //resalePrice
            std::cout <<" ,   "  << returnCsvItemSTOI(iss) << "  ,  ";
            //stats of attack...
            std::cout << returnCsvItemSTOI(iss) << "    ,    " << returnCsvItemSTOI(iss) << " , ";
            std::cout << returnCsvItemSTOI(iss) << "    ,    " << returnCsvItemSTOI(iss) << " , ";
            std::cout << returnCsvItemSTOI(iss) << "    ,    " << returnCsvItemSTOI(iss) << " , ";
            //object type
            std::cout <<"    ,    " <<returnCsvItemSTOI(iss);
            //name
            std::cout << "    ,    " <<returnCsvItem(iss);
            std::cout<<std::endl;
        }
    }
}

unsigned menu::returnCsvItemSTOI(std::istringstream & ss){
    std::string res;
    std::getline(ss,res,',');
    return std::stoi(res);
}


std::string menu::returnCsvItem(std::istringstream & ss){
    std::string res;
    std::getline(ss,res,',');
    return res;
}

unsigned menu::logicPlayer() {
    std::cout << spacingV1 << "What is your choice ? " << std::endl;

    unsigned input;
    bool correct=false;

    do{
        std::cin >> input;
        if(!std::cin) //input not a number
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<< "The input is incorrect no letters please, only numbers" << std::endl;
        }else{
            if(input == 1 || input == 2 || input == 3)
                correct = true;
            else{
                std::cout<< "The input is incorrect (1),(2) or (3) please" << std::endl;
            }
        }
    }while(correct==false);
    return input;
}
