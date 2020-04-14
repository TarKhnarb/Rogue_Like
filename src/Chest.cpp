#include "Chest.h"

Chest::Chest(Entity &aspen, orientation chestOrient):
        orient (chestOrient),
        chest (Inventory(1, 0, chestSize)),
        hero (aspen){}

void Chest::placeInChest(unsigned indexI) { // Prend l'index du Bag du joueur, PEUT ETRE UN PEU LEGER, A TESTER SI SUFFISANT

    unsigned objId = hero.getInventoryObject(indexI)->getId();
    unsigned objNb = hero.getInventoryObject(indexI)->getObjectNumber();
    unsigned objAdd = chest.addObjectNb(objId, objNb);

    if(objAdd == 0){
        hero.removeInventoryObject(indexI);
    }
    else{
        hero.removeInventoryObjectNb(objId, objNb-objAdd);
    }
}

void Chest::addInChest(unsigned id) {
    chest.addObject(id);
}

void Chest::removeFromChest(unsigned indexC) { // Prend l'index du coffre, PEUT ETRE UN PEU LEGER, A TESTER SI SUFFISANT

    unsigned objId = chest.getObject(indexC)->getId();
    unsigned objNb = chest.getObject(indexC)->getObjectNumber();
    unsigned objAdd = hero.addInventoryObjectNb(objId, objNb);

    if(objAdd == 0){
        chest.removeObject(indexC);
    }
    else{
        chest.removeObject(objId, objNb-objAdd);
    }
}

void Chest::loadChest(std::string fileName) {

    std::ifstream file (fileName);
    std::string csvItem;

    unsigned idObject, objectNb;
    unsigned line = 0;

    if (!file.is_open())
        throw std::runtime_error ("Chest::loadChest(std::string) - Failed to load from" + fileName);

    while (line < chestSize){

        getline(file,csvItem);
        std::istringstream iss(csvItem);

        if(csvItem != " "){
            idObject = returnCsvItemSTOI(iss);
            objectNb = returnCsvItemSTOI(iss);

            chest.addObject(idObject, objectNb);
        }

        line++;
    }
    file.close();
}

unsigned Chest::returnCsvItemSTOI(std::istringstream & ss){
    std::string res;
    std::getline(ss,res,',');
    return std::stoi(res);
}

void Chest::saveChest(std::string fileName) {
    std::ofstream file (fileName);
    if (!file.is_open())
    {
        throw std::runtime_error ("Chest::saveChest(std::string) - Failed to save in : " + fileName);
    }

    for(unsigned i = 0; i < chestSize; ++i){
        if(chest.getObject(i))
            file << chest.getObject(i)->getId() << ", " << chest.getObject(i)->getObjectNumber() << '\n';

        else
            file << " " << "," << '\n';
    }
    file.close();
}

void Chest::display() {
    chest.display();
}
