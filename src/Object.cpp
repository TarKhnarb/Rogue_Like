#include "Object.h"

Object::Object(unsigned id){

    std::ifstream file;
    std::string filename ("data/Objects.csv");
    file.open(filename);

    if (file.is_open()) {
        std::string csvItem;

        unsigned i = 0;
        while (i != id){
            if(file.eof()){
                throw std::runtime_error ("Failed to load id " + std::to_string(id));
            }
            getline(file,csvItem);
            i++;
        }
        std::istringstream iss(csvItem);

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
    }

    else{
        throw std::runtime_error ("Failed to load " + filename);
    }
    file.close();
}

unsigned Object::returnCsvItemSTOI(std::istringstream & ss){
    std::string res;
    std::getline(ss,res,',');
    return std::stoi(res);
}


std::string Object::returnCsvItem(std::istringstream & ss){
    std::string res;
    std::getline(ss,res,',');
    return res;
}

std::vector<int> Object::getStats() const{
    return stats;
}

unsigned Object::getId() const{
    return idObject;
}

std::string Object::getName() const{
    return name;
}

unsigned Object::getPrice() const{
    return price;
}

unsigned Object::getResalePrice() const{
    return resalePrice;
}

Object::Type Object::getType() const {
    return type;
}

unsigned Object::getObjectNumber() const {
    return objectNumber;
}

unsigned Object::addObjectNumber(unsigned nb) {
	unsigned place = getMaxStack() - objectNumber;

	if (nb > place){

		objectNumber = getMaxStack();
		return nb - place;
	}
	else{

		objectNumber += nb;
		return 0;
	}
}

void Object::setObjectNumber(unsigned i) {
    objectNumber = i;
}

unsigned Object::getMaxStack() const {

    switch (type){
        case Type::monsterLoot:
            return 16u;

        default:
            return 1u;
    }
}

//mainly for debug
void Object::display(){

    std::cout << "      idObject     : " << idObject << std::endl;
    std::cout << "      price        : " << price << std::endl;
    std::cout << "      resalePrice  : " << resalePrice << std::endl;
    std::cout << "      objectNumber : " << objectNumber << std::endl;

    // fly, attack, attackSpeed, hp, defense, speed
    std::cout << "      fly          : " << stats[0] << std::endl;
    std::cout << "      attack       : " << stats[1] << std::endl;
    std::cout << "      attackSpeed  : " << stats[2] << std::endl;
    std::cout << "      hp           : " << stats[3] << std::endl;
    std::cout << "      defence      : " << stats[4] << std::endl;
    std::cout << "      speed        : " << stats[5] << std::endl;

    std::cout << "      type         : " << type << std::endl;
    std::cout << "      name         : " << name << std::endl;
    std::cout << std::endl;
}
