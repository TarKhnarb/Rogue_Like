#include "menu.h"


std::string spacingV1(100/2, ' ');
std::string spacingV2(40, ' ');
std::string spacingV3(50/4, ' ');
std::string spacingV4 = "    ,    ";

void menu::logic(){
    Entity * Aspen(0,0);
    while(choice != 4){//until 4 is not chosen keep in menu
        system("clear");
        rules();
        choice = logicPlayer(1);
        switch(choice){
            case 1 :
                buyObject(Aspen);
                break;
            case 2 :
                sellObject(Aspen);
                break;
            case 3 :
                showPlayer(Aspen);
                break;
            default :
                break;
        }
    }
    game::game();
}

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
    sub_rules();
    displayBounds();
}

void menu::sub_rules(){
    std::cout<<std::endl;
    std::cout<< spacingV3 << "Please type in the corresponding number in the console of what you want to do : " <<std::endl;
    std::cout<<std::endl;
    std::cout<< spacingV3 << "- One(1) to buy an object and add it to your inventory" << std::endl;
    std::cout<< spacingV3 << "- two(2) to sell an object of your player inventory" <<std::endl;
    std::cout<< spacingV3 << "- Three(3) to show your player with all his stats and inventory" <<std::endl;
    std::cout<< spacingV3 << "- Four(4) to go to the game and play against monsters and TRYNNA win" <<std::endl;
    std::cout<<std::endl;
    std::cout<< spacingV3 << "- Other inputs will not be taken into account" << std::endl;
    std::cout << spacingV3 <<"- You can now make your choice in the console " <<std::endl;
    std::cout<<std::endl;
}

void menu::showPlayer(Entity * Aspen) {
    system("clear");
    std::cout << spacingV3 << "This is your player with his current inventory and statistics" << std::endl;
    Aspen->displayEntity();
    std::cout<<std::endl;
    std::cout << spacingV3 << "If you think you have enough, you might go to war"<< std::endl;
    std::cout << spacingV3 << "If not buy and sell some inventory stuff to get MORE POWERFUl and RICHER" <<std::endl;
    std::cout << std::endl;
    sub_rules();
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

unsigned menu::logicPlayer(const unsigned & menu_choice) {
    std::cout << spacingV3 << "What is your choice ? " << std::endl;

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
            if(menu_choice==1) {
                if (input >= 1 && input <= 4 )
                    correct = true;
                else {
                    std::cout << "The input is incorrect (1),(2) or (3) please" << std::endl;
                }
            }
            else{
                if(input >= 1 && input <=7)
                    correct = true;
                else{
                    std::cout<< "The input is incorrect, your choice ranges between one(1) and seven(7) please" << std::endl;
                }
            }
        }
    }while(!correct);
    return input;
}

void menu::buyObject(Entity * Aspen){
    system("clear");
    showDB();
    unsigned objectID;
    std::cout<< spacingV3 << "Tell me what you wanna buy by writing down it's id (a number)" << std::endl;
    objectID = logicPlayer(2);

    Aspen->buyObject(objectID,1);

    system("clear");
    std::cout<< spacingV3 << "Your choice has been taken into account. Thank you" << std::endl;
    std::cout << spacingV3 << "Please wait " << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(3));

    std::cout << std::endl;
    system("clear");
}


void menu::sellObject(Entity * Aspen){
    system("clear");
    showPlayer(Aspen);
    unsigned objectID;
    std::cout<< spacingV3 << "Tell me what you wanna sell by writing down it's id (a number)" << std::endl;
    objectID = logicPlayer(2);

    Aspen->sellObject(objectID,1);

    system("clear");
    std::cout<< spacingV3 << "Your choice has been taken into account. Thank you" << std::endl;
    std::cout << spacingV3 << "Please wait " << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(3));

    system("clear");
}

Entity* menu::returnEntity(){
    return Aspen;
