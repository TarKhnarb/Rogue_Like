#include "Upgrade.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>

Upgrade::Upgrade(unsigned id, unsigned choice) {
    assert((choice==1)||(choice==2));
    bool trouve = false;
    std::ifstream file;
    std::cout << "11" << std::endl;
    if(choice==1)  {
        file.open("data/Upgrades.csv");
    }
    if(choice==2)   {
        file.open("data/Make.csv");
    }
    std::cout << "22" << std::endl;
       if (file.is_open()) {
           std::string csvItem;

           unsigned i = 0;
           while (i != id){
               if(file.eof()){
                   std::cout << "The object id you are searching for is too big" << std::endl;
               }
               getline(file,csvItem);
               i++;
           }
           trouve = true;
           std::cout << "i = " << i << std::endl;
           std::cout << "33" << std::endl;
       if (trouve) {
           std::istringstream iss(csvItem);
           for (unsigned i = 0; i < resourcesSize; ++i) {
               std::string res;
               std::getline(iss, res, ',');
               unsigned t = std::stoi(res);
               resources.push_back(t);
           }
           std::string res;
           std::getline(iss, res, ',');
           price = std::stoi(res);
       }
       else {
            std::cerr << " something went wrong " << std::endl;
       }
   }
    file.close();
}


std::vector<unsigned> Upgrade::getResource() const {
    return resources;
}


unsigned Upgrade::getPrice() const {
    return price;
}




void Upgrade::display() const {
    std::cout << "Pour améliorer l'object d'identifiant " << resources[0] << std::endl;
    for(int i = 1; i < 10; i++)
    {
        if(i%2 != 0)
        {
            std::cout << "On aura besoin de l'object n°" << resources[i];
        }
        else std::cout << "au nombre de " << resources[i] << std::endl;
    }
    std::cout << "Son prix est de " << price << std::endl;
}



void Upgrade::Test() {
    Upgrade up(1,1);
    up.display();
    Upgrade upg(2,1);
    upg.display();

    std::cout << "Utilisation des fonctions accesseurs : " << std::endl;
    std::cout << "Le prix de l'upgrade 2 est " << upg.getPrice() << std::endl;

    std::vector<unsigned> Resources2 = upg.getResource();
    std::cout << "Les ressources à avoir sont : " << std::endl;
    for(unsigned i = 1; i < 9; i++)   {
        std::cout << "On a besoin de " << Resources2[i+1] << " object n° " << Resources2[i] << std::endl;
        i++;
    }
}