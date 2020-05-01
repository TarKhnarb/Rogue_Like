#include "Upgrade.h"

Upgrade::Upgrade(unsigned id) {

    std::ifstream file;
    std::string filename = "data/Upgrades.csv";
    file.open(filename);

    if (file.is_open()) {
        std::string csvItem;

        unsigned i = 10;
        while (i != id) {
            if (file.eof()) {
                std::cout << "The object id you are searching for is too big" << std::endl;
            }
            getline(file, csvItem);
            i++;
        }

        std::istringstream iss(csvItem);
        for (unsigned i = 0; i < resourcesSize; ++i) {
            unsigned t = returnCsvItemSTOI(iss);
            resources.push_back(t);
        }

    }
    else{
        throw std::runtime_error ("Failed to load " + filename);
    }

    file.close();
}

unsigned Upgrade::returnCsvItemSTOI(std::istringstream & ss){
    std::string res;
    std::getline(ss,res,',');
    return std::stoi(res);
}

std::vector<unsigned> Upgrade::getResource() const {
    return resources;
}

unsigned Upgrade::getId() const {
    return resources[0];
}


void Upgrade::display() const {

    std::cout << "Pour améliorer l'object d'identifiant " << resources[0] << std::endl;
    std::cout << std::endl;
    for(int i = 1; i < 9; i++)
    {
        if(resources[i] != 0){
            if(i%2 != 0){
                std::cout << "On aura besoin de l'object n°" << resources[i];
            }
            else std::cout << "au nombre de " << resources[i] << std::endl;

            std::cout << std::endl;
        }
    }
}
