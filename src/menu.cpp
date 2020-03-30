#include "menu.h"


std::string spacingV1(100/2, ' ');
std::string spacingV2(40, ' ');
std::string spacingV3(50/4, ' ');
std::string spacingV4 = "    ,    ";

menu::menu(): Aspen (Entity(0, 0)), gameWindow (WinTXT(27,27)){}


void menu::logic() {
    Aspen.setPosition(0, 0); // Au cas où
    bool tgame = false;
    bool quit = false;

    do{
        system("clear");
        rules();
        choice = gameWindow.getCh();

        switch (choice) {
            case 'b' :
                std::this_thread::sleep_for(std::chrono::seconds(1));
                choice = 1;
                buyObjectMenu();
                break;
            case 's' :
                std::this_thread::sleep_for(std::chrono::seconds(1));
                choice = 1;
                sellObjectMenu();
                break;
            case 'p' :
                std::this_thread::sleep_for(std::chrono::seconds(1));
                choice = 1;
                showPlayer();
                break;

            case 'g' :
                tgame = true;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;

            case 'q':
                quit = true;

            default :
                std::this_thread::sleep_for(std::chrono::seconds(1));
                choice = 1;
                break;
            }
        system("clear");

    } while(!tgame || quit); //until 'g' not chosen stay in loop

    if(!quit){
        game theGame = game(Aspen);
        while (theGame.getTestgame()) {
            theGame.gameLoop(gameWindow.getCh());
            tgame = theGame.getTestgame();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            system("clear");
        }
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
    std::cout<< spacingV3 << "Please type in the corresponding letter in the console of what you want to do : " <<std::endl;
    std::cout<<std::endl;
    std::cout<< spacingV3 << "  - b(buy)    to buy an object and add it to your inventory" << std::endl;
    std::cout<< spacingV3 << "  - s(sell)   to sell an object of your player inventory" <<std::endl;
    std::cout<< spacingV3 << "  - p(player) to show your player with all his stats and inventory" <<std::endl;
    std::cout<< spacingV3 << "  - g(game)   to go to the game and play against monsters and TRYNNA win" <<std::endl;
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
    std::cout << spacingV3 << "If not buy and sell some inventory stuff to get MORE POWERFUl and RICHER" << std::endl;
    std::cout << std::endl;

    std::cout << "      0  + ENTER_KEY : Retour" << std::endl;
    int check;
    do{
        std::cin >> check;
    }while(check != 0);

    sub_rules();
}

void menu::showDB() {
	std::cout<<std::endl;
    //showing the csv file
    std::ifstream file;
    file.open("data/Objects.csv");

    if (file.is_open()) {

        std::string csvItem;

        std::cout << "Here are the stats of the objects you can buy : " << std::endl;
        std::cout << std::endl;
        std::cout << "id, price, resalePrice, fly, attack, attackSpeed, hp, defence, speed, type, name" << std::endl;
        std::cout << std::endl;
        getline(file, csvItem);

        for (unsigned i = 1; i < 8; ++i) { //display stats objects from csv file
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

    system("clear");
    showDB();
    std::cout << spacingV3 << "Tell me what you wanna buy by writing down it's corresponding id number then PRESS enter" << std::endl;
	
	int buy;
	do{
        	std::cin >> buy;
	}while(buy < 1 || buy > 8);

    Aspen.buyObject(buy,1);

    system("clear");
    std::cout<< spacingV3 << "Your choice has been taken into account. Thank you" << std::endl;
    std::cout << spacingV3 << "Please wait " << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(3));

    std::cout << std::endl;
    system("clear");
}


void menu::sellObjectMenu() {

    system("clear");

    if(!Aspen.inventoryEmpty()){

        Aspen.displayEntity();

        std::cout << spacingV3 << "Tell me what you wanna sell by writing down it's id (a number) and then PRESS enter" << std::endl;

        int sell;
        do{
            std::cin >> sell;
        }while(sell < 1 || sell > 8);

	    Aspen.sellObject(sell, 1);

        system("clear");
        std::cout << spacingV3 << "Your choice has been taken into account. Thank you" << std::endl;
        std::cout << spacingV3 << "Please wait " << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    else{
        std::cout << "Vous ne possedez aucun objet, taper 1 pour en acheter" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}