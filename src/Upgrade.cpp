#include "Upgrade.h"
/*


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


std::vector<unsigned> Upgrade::getResource(unsigned id) const {
    return resources;
}


unsigned getPrice(unsigned idObject) const {
    return price;
}*/