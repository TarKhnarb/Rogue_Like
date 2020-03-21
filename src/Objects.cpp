#include "Objects.h"

#include <iostream>

Object::Object(unsigned id){

    sqlite3* Object;
    sqlite3_stmt* requete = 0;
    const unsigned statment = 10;

    const char *pSQL[statment];

    int base = sqlite3_open("/data/Objects.db", &Object);
    assert(!base);

    pSQL[0] = "SELECT name FROM Object WHERE idObject = ?"; // requête de selection d'objet
    pSQL[1] = "SELECT price FROM Object WHERE idObject = ?";
    pSQL[2] = "SELECT resalePrice FROM Object WHERE idObject = ?";
    pSQL[3] = "SELECT fly FROM Object WHERE idObject = ?";
    pSQL[4] = "SELECT attack FROM Object WHERE idObject = ?";
    pSQL[5] = "SELECT attackSpeed FROM Object WHERE idObject = ?";
    pSQL[6] = "SELECT hp FROM Object WHERE idObject = ?";
    pSQL[7] = "SELECT defence FROM Object WHERE idObject = ?";
    pSQL[8] = "SELECT speed FROM Object WHERE idObject = ?";
    pSQL[9] = "SELECT type FROM Object WHERE idObject = ?";


    for(unsigned i = 0; i < statment; ++i){

        base = sqlite3_prepare(Object, pSQL[i], -1, &requete, 0);
        /*
         * On prépare les requêtes en mettant ? à la place des paramètres
         * -1 --> détection automatique de la taille de psQL[i]
         */

        assert(base == SQLITE_OK || requete != 0);

        sqlite3_bind_int(requete, 1, id); // On remplace ? (1 : 1er de la requête (max 4)) par id

        base = sqlite3_step(requete);

        switch (base){
            case SQLITE_ROW: // Enregistrement trouvé
                switch(i) {
                    case 0:
                        name = base;
                        break;

                    case 1:
                        price = base;
                        break;

                    case 2:
                        resalePrice =  base;
                        break;

                    case 3:
                        stats.push_back(base); //fly
                        break;

                    case 4:
                        stats.push_back(base); // attack
                        break;

                    case 5:
                        stats.push_back(base); // attackSpeed
                        break;
                    case 6:
                        stats.push_back(base); // hp
                        break;

                    case 7:
                        stats.push_back(base); // defence
                        break;

                    case 8:
                        stats.push_back(base); // speed
                        break;

                    case 9:
                        switch (base){
                            case 0:
                                type = Type::basicStat;
                                break;

                            case 1:
                                type = Type::projectile;
                                break;

                            case 2:
                                type = Type::armor;
                                break;

                            case 3:
                                type = Type::amulet;
                                break;

                            case 4:
                                type = Type::monsterLoot;
                                break;

                            default:
                                break;
                        }
                        break;

                    default:
                        break;
                }
                break;

            case SQLITE_DONE:
                std::cout << "Aucun enregistrement trouvé" << std::endl;
                break;

            default:
                std::cout << "Problème lors de l'exécution de la requête" << std::endl;

        }
        sqlite3_finalize(requete); // Termine la requête
    }

    sqlite3_close(Object); //Ferme la base

    objectNumber = 1;

}

Object::~Object() {
    name.clear();
    stats.clear();
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

Object::Type Object::getObjectType() const {
    return type;
}

unsigned Object::getObjectNumber() const {
    return objectNumber;
}

void Object::setObjectNumber(unsigned i) {
    objectNumber = i;
}

const unsigned Object::getMaxStack() const {

    switch (type){
        case Type::monsterLoot:
            return 16u;

        default:
            return 1u;
    }
}
/*
 * unsigned idObject;
    std::string name;
    unsigned price;
    unsigned resalePrice;
    Type type;
    unsigned objectNumber;
 */

// fly, attack, attackSpeed, hp, defense, speed

//utile pour le debug
void Object::display(){

    std::cout << "      idObject : " << idObject << std::endl;
    std::cout << "      name : " << name << std::endl;
    std::cout << "      price : " << price << std::endl;
    std::cout << "      resalePrice : " << resalePrice << std::endl;
    std::cout << "      type : " << type << std::endl;
    std::cout << "      objectNumber : " << objectNumber << std::endl;
    std::cout << "      fly : " << stats[0] << std::endl;
    std::cout << "      attack : " << stats[1] << std::endl;
    std::cout << "      attackSpeed : " << stats[2] << std::endl;
    std::cout << "      hp : " << stats[3] << std::endl;
    std::cout << "      defence : " << stats[4] << std::endl;
    std::cout << "      fly : " << stats[5] << std::endl;

    std::cout << std::endl;
}