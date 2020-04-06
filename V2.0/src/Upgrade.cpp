#include "Upgrade.h"

#include <fstream>
#include <iostream>
#include <sstream>


Upgrade::Upgrade(unsigned id) {

    std::ifstream file;
    file.open("data/Upgrades.csv");

   if (file.is_open()) {
       std::string csvItem;

       unsigned i = 0;
       while (i != id) {
           if (file.eof()) {
               std::cout << "The object id you are searching for is too big" << std::endl;
           }
           getline(file, csvItem);
           i++;
       }
       std::istringstream iss(csvItem);

       for (unsigned i = 0; i < resourcesSize; ++i) {
           std::string res;
           std::getline(iss,res,',');
           unsigned t =  std::stoi(res);
           resources.push_back(t);
       }
       std::string res;
       std::getline(iss,res,',');
       price = std::stoi(res);
   }

   else{
       std::cerr <<" something went wrong "<< std::endl;
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
    for(int i = 1; i < 9; i++)
    {
        if(i%2 != 0)
        {
            std::cout << "On aura besoin de l'object n°" << resources[i];
        }
        else std::cout << " au nombre de " << resources[i] << std::endl;
    }
    std::cout << "Son prix est de " << price << std::endl;
}

void Upgrade::Test() {
    Upgrade up(1);
    up.display();
    Upgrade upg(2);
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