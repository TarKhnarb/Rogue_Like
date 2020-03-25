#include "Upgrade.h"
/*
Upgrade* getResource(unsigned id) const {
    assert(id >= 0);

    std::ifstream file;
    file.open("./data/upgrade.csv");

    if (file.is_open()) {
        std::string csvItem;

        unsigned i = 0;
        while(i != id){
            if(file.eof()){
                std::cout << "The object id you are searching for is too big" << std::endl;
            }
            getline(file,csvItem);
            i++;
        }
        std::istringstream iss(csvItem);

        idObject = returnCsvItemSTOI(iss);
        price = returnCsvItemSTOI(iss);
        idObjN1 = returnCsvItemSTOI(iss);
        numberObjN1 = returnCsvItemSTOI(iss);
        idObjN2 = returnCsvItemSTOI(iss);
        numberObjN2 = returnCsvItemSTOI(iss);
        idObjN3 = returnCsvItemSTOI(iss);
        numberObjN3 = returnCsvItemSTOI(iss);
        idObjN4 = returnCsvItemSTOI(iss);
        numberObjN4 = returnCsvItemSTOI(iss);
    }
    else{
        std::cerr <<" something went wrong "<< std::endl;
    }
}

/*
unsigned getPrice(unsigned idObject) const {
    return price;
}
*/