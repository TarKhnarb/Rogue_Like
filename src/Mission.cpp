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

        unsigned t = returnCsvItemSTOI(iss);
        switch (t){
            case 0:
                typeQuest = Type::obtain;
                break;
            case 1:
                typeQuest = Type::step;
                break;
            default:
                break;
        }
        if(typeQuest == Type::obtain) {
            unsigned w = returnCsvItemSTOI(iss);
            switch (w) {
                case 0:
                    typeObtainQuest = TypeObtain::object;
                    break;
                case 1:
                    typeObtainQuest = TypeObtain::loot;
                    break;
                case 2:
                    typeObtainQuest = TypeObtain::potion;
                    break;
                case 3:
                    typeObtainQuest = TypeObtain::upgrade;
                    break;
                case 4:
                    typeObtainQuest = TypeObtain::specific;
                    break;
                default:
                    break;
            }
        }
        else
            typeObtainQuest = TypeObtain::nullO;
        nbCopyORid = returnCsvItemSTOI(iss);
        nbCopyObtain = 0;
    }
    else{
        std::cerr <<" something went wrong "<< std::endl;
    }
    file.close();
}


void Mission::update(Entity* hero,Mission mis1,Mission mis2){
    if(!Complete){
        switch(typeQuest){
            case Type::obtain :
                updateTypeObtain(hero);
                break;
            case Type::step :
                if((mis1.Complete)&&(mis2.Complete))
                {
                    Complete = true;
                }
                break;
            default :
                break;
        }
    }
}

void Mission::isComplete() const{
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


bool Mission::getComplete() const {
    return Complete;
}


void Mission::updateTypeObtain(Entity* hero){
    switch(typeObtainQuest)
    {
        case TypeObtain::object :
            for(unsigned i = 11; i < 47 ; i+=3)
            {
                if(hero->isItOnEntity(i,1)) nbCopyObtain++;
                if(nbCopyORid==nbCopyObtain)
                {
                    Complete = true;
                    i = 47;
                }
            }
            break;
        case TypeObtain::loot :
            for(unsigned i = 50; i < 64 ; i++)
            {
                if(hero->isItOnEntity(i,1)) nbCopyObtain++;
                if(nbCopyORid==nbCopyObtain)
                {
                    Complete = true;
                    i = 64;
                }
            }
            break;
        case TypeObtain::potion :
            for(unsigned i = 47; i < 50 ; i++)
            {
                if(hero->isItOnEntity(i,1)) nbCopyObtain++;
                if(nbCopyORid==nbCopyObtain)
                {
                    Complete = true;
                    i = 50;
                }
            }
            break;
        case TypeObtain::upgrade :
            for(unsigned i = 12; i < 47 ; i+=3)
            {
                if(hero->isItOnEntity(i,1)) nbCopyObtain++;
                if(hero->isItOnEntity(i+1,1)) nbCopyObtain++;
                if(nbCopyORid==nbCopyObtain)
                {
                    Complete = true;
                    i = 47;
                }
            }
            break;
        case TypeObtain::specific :
            if(hero->isItOnEntity(nbCopyORid,1))
            {
                Complete = true;
            }
        default :
            break;
    }
}
