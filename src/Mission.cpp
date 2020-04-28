#include "Mission.h"

Mission::Mission(unsigned id){

    std::ifstream file;
    file.open("data/Mission.csv");

    if (file.is_open()) {
        std::string csvItem;

        unsigned i = 0;
        while (i != id){
            if(file.eof()){
                std::cout << "Error you try to create a quest which not exists" << std::endl;
            }
            getline(file,csvItem);
            i++;
        }
        std::istringstream iss(csvItem);

        idQuest = returnCsvItemSTOI(iss);
        Quest = returnCsvItem(iss);
        Complete = false;


        /*
        idObject = returnCsvItemSTOI(iss);
        price = returnCsvItemSTOI(iss);
        resalePrice = returnCsvItemSTOI(iss);
        objectNumber = 1;

        for(unsigned i=0;i<statSize;++i){
            unsigned t = returnCsvItemSTOI(iss);
            stats.push_back(t);
        }
        unsigned t = returnCsvItemSTOI(iss);
        switch (t){
            case 0:
                type = Type::basicStat;
                break;
            case 1:
                type = Type::helmet;
                break;
            case 2:
                type = Type::chestplate;
                break;
            case 3:
                type = Type::leggings;
                break;
            case 4:
                type = Type::boots;
                break;
            case 5:
                type = Type::projectile;
                break;
            case 6:
                type = Type::amulet;
                break;
            case 7:
                type = Type::potion;
                break;
            case 8:
                type = Type::monsterLoot;
            default:
                break;
        }

        name = returnCsvItem(iss);
         */
    }

    else{
        std::cerr <<" something went wrong "<< std::endl;
    }
    file.close();
}

void Mission::Upgrade(const Entity& hero,Mission mis1,Mission mis2){
    switch(idQuest){
        case 1 :
            for(unsigned i = 11; i < 47 ; i+=3)
            {
                if(hero.isItOnEntity(i,1))
                {
                    Complete = true;
                }
            }
            break;
        case 2 :
            for(unsigned i = 47; i < 50 ; i++)
            {
                if(hero.isItOnEntity(i,1))
                {
                    Complete = true;
                }
            }
            break;
        case 3 :
            if((mis1.Complete)&&(mis2.Complete))
            {
                Complete = true;
            }
            break;
        case 4 :
            /*if(hero.isDead())
            {
                Complete = true;
            }*/
            break;
        case 5 :
            std::cout << idQuest;
            break;
        default :
            break;
    }
}

void Mission::isComplete(){
    if(Complete){
        std::cout << std::endl;
        std::cout << "La mission a été réussie";
    }
    else{
        std::cout << std::endl;
        std::cout << "La mission n'a pas été réussie";
    }
}

unsigned Mission::returnCsvItemSTOI(std::istringstream & ss){
    std::string res;
    std::getline(ss,res,',');
    return std::stoi(res);
}


std::string Mission::returnCsvItem(std::istringstream & ss){
    std::string res;
    std::getline(ss,res,',');
    return res;
}


void Mission::setComplete(bool t)
{
   Complete = t;
}