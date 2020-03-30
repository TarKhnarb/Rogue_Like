#include "menu.h"

std::string spacingV1(100/2, ' ');
std::string spacingV2(40, ' ');
std::string spacingV3(50/4, ' ');
std::string spacingV4 = "    ,    ";

menu::menu(): Aspen (Entity(0, 0)), gameWindow (WinTXT(27,27)){}


void menu::logic() {
    Aspen.setPosition(0, 0); // Au cas où
/*
    while (choice != 4) { //until 4 is not chosen keep in menu
        system("clear");
        rules();
        choice = gameWindow.getCh();

        switch (choice) {
            case '1' :
                std::this_thread::sleep_for(std::chrono::seconds(1));
                buyObjectMenu();
                break;
            case '2' :
                std::this_thread::sleep_for(std::chrono::seconds(1));
                sellObjectMenu();
                break;
            case '3' :
                std::this_thread::sleep_for(std::chrono::seconds(1));
                showPlayer();
                break;
            default :
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
        }
        system("clear");
    }*/

    game theGame = game(Aspen);
    while (theGame.getTestgame()) {
        theGame.gameLoop(gameWindow.getCh());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("clear");
    }
}

void menu::displayBounds() {
    for(unsigned i = 0; i < console_size; ++i){
        std::cout<<"-";
    }
    std::cout<<std::endl;
}

void menu::rules(){
    displayBounds();

    std::cout<< spacingV1 << "Hello,"<<std::endl;
    std::cout<< spacingV2 << "You are in the main menu game"<<std::endl;
    std::cout<<std::endl;
    sub_rules();
    displayBounds();
}

void menu::sub_rules() {

    std::cout<<std::endl;
    std::cout<< spacingV3 << "Please type in the corresponding number in the console of what you want to do : " <<std::endl;
    std::cout<<std::endl;
    std::cout<< spacingV3 << "  - One(1) to buy an object and add it to your inventory" << std::endl;
    std::cout<< spacingV3 << "  - two(2) to sell an object of your player inventory" <<std::endl;
    std::cout<< spacingV3 << "  - Three(3) to show your player with all his stats and inventory" <<std::endl;
    std::cout<< spacingV3 << "  - Four(4) to go to the game and play against monsters and TRYNNA win" <<std::endl;
    std::cout<<std::endl;
    std::cout<< spacingV3 << "  - Other inputs will not be taken into account" << std::endl;
    std::cout << spacingV3 <<"  - You can now make your choice in the console " <<std::endl;
    std::cout<<std::endl;
}

void menu::showPlayer() {
    system("clear");
    std::cout << spacingV3 << "This is your player with his current inventory and statistics" << std::endl;

    Aspen.displayEntity();

    std::cout<<std::endl;
    std::cout << spacingV3 << "If you think you have enough, you might go to war"<< std::endl;
    std::cout << spacingV3 << "If not buy and sell some inventory stuff to get MORE POWERFUl and RICHER" <<std::endl;
    std::cout << std::endl;
    sub_rules();
}

void menu::showDB() {
	std::cout<<std::endl;
    //showing the csv file
    std::ifstream file;
    file.open("data/Objects.csv"); //verify path >> makefile

    if (file.is_open()) {

        std::string csvItem;

        std::cout << "Here are the stats of the objects you can buy : " << std::endl;
        std::cout << std::endl;
        std::cout << "id, price, resalePrice, fly, attack, attackSpeed, hp, defence, speed, type, name" << std::endl;
        std::cout << std::endl;
        getline(file, csvItem);

        for (unsigned i = 1; i < 6; ++i) { //display stats objects from csv file
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
    std::cout<<std::endl;
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

void menu::buyObjectMenu(){

    while (2 > choice && choice > 8){
        system("clear");
        showDB();

        std::cout << spacingV3 << "Tell me what you wanna buy by writing down it's id (a number)" << std::endl;

        choice = gameWindow.getCh();
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    if(choice < 2 || choice > 8){
        Aspen.buyObject(choice,1);

        system("clear");
        std::cout<< spacingV3 << "Your choice has been taken into account. Thank you" << std::endl;
        std::cout << spacingV3 << "Please wait " << std::endl;
        std::this_thread::sleep_for (std::chrono::seconds(3));

        std::cout << std::endl;
        system("clear");
    }
    else{
        system("clear");
        std::cout << "Veuillez saisir un id correspondant à la liste formie" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }


}


void menu::sellObjectMenu() {

    while (!Aspen.inventoryEmpty()) {
        system("clear");
        showPlayer();
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << spacingV3 << "Tell me what you wanna sell by writing down it's id (a number)" << std::endl;

        choice = gameWindow.getCh();
    }
    if(!Aspen.inventoryEmpty()){
        Aspen.sellObject(choice, 1);

        system("clear");
        std::cout << spacingV3 << "Your choice has been taken into account. Thank you" << std::endl;
        std::cout << spacingV3 << "Please wait " << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    else{
        system("clear");
        std::cout << "Vous ne possedez aucun objet, taper 1 pour en acheter" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}