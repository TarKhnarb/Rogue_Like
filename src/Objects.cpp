#include "Objects.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <assert.h>

Object::Object(unsigned id){

    sqlite3* Object;
    sqlite3_stmt* requete = 0;
    const unsigned statment = 4;

    const char *pSQL[statment];

    int base = sqlite3_open("/data/Objects.db", &Object);
    assert(!base);

    pSQL[0] = "SELECT name FROM Object WHERE idObject = ?"; // requête de selection d'objet
    pSQL[1] = "SELECT price FROM Object WHERE idObject = ?";
    pSQL[2] = "SELECT resalePrice FROM Object WHERE idObject = ?";
    pSQL[3] = "SELECT jump FROM Object WHERE idObject = ?";

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
                        name = reinterpret_cast<const char*> (sqlite3_column_text(requete, 0));
                        break;

                    case 1:
                        price = int(reinterpret_cast<const char*> (sqlite3_column_text(requete, 0)));
                        break;

                    case 2:
                        resalePrice = int(reinterpret_cast<const char*> (sqlite3_column_text(requete, 0)));
                        break;

                    case 3:
                        jump = reinterpret_cast<const char*> (sqlite3_column_text(requete, 0));
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
            iss >> jump;

            while (iss >> variable) {
                stats.push_back(stoi(variable));
            }
        }
        else{ //revoir peut etre inutile >> meilleur solution >> eviter l'init du cons en renvoyant code erreur
            std::cout<<"The id : "<<id <<" of the object you are searching for is too big"<<std::endl;
            unsigned defaultValue=0;
            std::string defaultName = "no name";
            idObject = price = resalePrice = jump = defaultValue;
            name = defaultName;
            stats.push_back(defaultValue);
        }
    }else{
        std::cout<<"Unable to open file for some reason"<<std::endl;
    }
    file.close();
}
*/
Object::~Object() {
    //verifier si utile de faire les id=0...etc car de toute façon object est destroy
    idObject=0;
    price=0;
    resalePrice=0;

    jump=false;
    name.clear();
    stats.clear();
}

unsigned Object::getId() const{
    return idObject;
}

unsigned Object::getPrice() const{
    return price;
}

unsigned Object::getResalePrice() const{
    return resalePrice;
}

bool Object::getJump() const{
    return jump;
}

std::string Object::getName() const{
    return name;
}

std::vector<unsigned> Object::getStats() const{
    return stats;
}

//utile pour le debug
void Object::display(){
    std::cout<<idObject<< " " << name << std::endl;
    std::cout<< price << " " << resalePrice << " " << jump<<std::endl;
    for(auto i=stats.begin();i<stats.end();i++){
       std::cout<<*i<< " ";
    }
    std::cout<<std::endl;
}