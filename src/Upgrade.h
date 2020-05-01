#ifndef _UPGRADE_H
#define _UPGRADE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <stdexcept>

const unsigned resourcesSize = 9;
const unsigned minIdEquipment = 11;
const unsigned maxIdEquipement = 49;

class Upgrade {

public:
    Upgrade(unsigned);

    std::vector<unsigned> getResource() const;

    unsigned getId() const;

    void display() const;

    void Test();

private:
    unsigned returnCsvItemSTOI(std::istringstream &);

    std::vector<unsigned> resources;  //idUpgrade, idObjN1, numberObjN1, idObjN2, numberObjN2, idObjN3, numberObjN3, idObjN4,  numberObjN4
    unsigned price;
};

#endif

// Forme du fichier  ATTENTION pour que la lecture soit plus simple il faut que les ligne aient le même nombre
// d'élements quitte a les mettres a 0 comme ca simple condition a faire pour verifier si on garde idObjN°_

// idObject, idResourceNb1, nbCopyNb1, idResourceNb2, nbCopyNb2, idResourceNb3, nbCopyNb3, idResourceNb4, nbCopyNb4
