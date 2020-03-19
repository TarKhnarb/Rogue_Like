#include "Objects.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>

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

        sqlite3_bind_int(requete, 1, id); // On remplace ? (1er de la requête) par id

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
                        fly = base;
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
        sqlite3_finalize(requete);
    }

    sqlite3_close(Object); //Ferme la base

}

Object::~Object() {
    name.clear();
    stats.clear();
}

/*
Object::Objects(unsigned id) {
    assert(id>0);
    std::ifstream file;
    file.open("objects.txt"); //fichier contenant sur chaque ligne les stats d'un object

    if(file.is_open()){
        std::string variable;

        //saute des lignes si id > 1 >> recup d'object autre que le premier
        unsigned i=0;
        do{
            getline(file,variable);
            ++i;
        }while(!file.eof() && i < id+2); //2= nb_ligne-1 qu'il faut pas lire
        if(!file.eof()) {
            std::istringstream iss(variable);
            //recuperation des données
            iss >> idObject;
            iss >> name;
            iss >> price;
            iss >> resalePrice;
            iss >> fly;

            while (iss >> variable) {
                stats.push_back(stoi(variable));
            }
        }
        else{ //revoir peut etre inutile >> meilleur solution >> eviter l'init du cons en renvoyant code erreur
            std::cout<<"The id : "<<id <<" of the object you are searching for is too big"<<std::endl;
            unsigned defaultValue=0;
            std::string defaultName = "no name";
            idObject = price = resalePrice = fly = defaultValue;
            name = defaultName;
            stats.push_back(defaultValue);
        }
    }else{
        std::cout<<"Unable to open file for some reason"<<std::endl;
    }
    file.close();
}

Object::~Object() {
    //verifier si utile de faire les id=0...etc car de toute façon object est destroy
    idObject=0;
    price=0;
    resalePrice=0;

    fly=false;
    name.clear();
    stats.clear();
}*/

unsigned Object::getId() const{
    return idObject;
}

unsigned Object::getPrice() const{
    return price;
}

unsigned Object::getResalePrice() const{
    return resalePrice;
}

bool Object::getFly(){
    return fly;
}

unsigned Object::getAttack() const {
    return stats[0];
}

unsigned Object::getAttackSpeed() const {
    return stats[1];
}

unsigned Object::getHp() const {
    return stats[2];
}

unsigned Object::getDefence() const {
    return stats[3];
}

unsigned Object::getSpeed() const {
    return stats[4];
}

std::string Object::getName() const{
    return name;
}

std::vector<unsigned> Object::getStats() const{
    return stats;
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