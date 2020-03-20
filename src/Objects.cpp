#include "Objects.h"

#include <iostream>

Object::Object(unsigned id){

    sqlite3* Object;
    sqlite3_stmt* requete = 0;
    const unsigned statment = 9;

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


    for(unsigned i = 0; i < statment; i++){

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

/*
//utile pour le debug
void Object::display(){
    std::cout<<idObject<< " " << name << std::endl;
    std::cout<< price << " " << resalePrice << " " << fly<<std::endl;
    for(auto i=stats.begin();i<stats.end();i++){
       std::cout<<*i<< " ";
    }
    std::cout<<std::endl;
}*/