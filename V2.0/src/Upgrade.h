#ifndef _UPGRADE_H
#define _UPGRADE_H

#include <vector>

const unsigned resourcesSize = 9;
const unsigned maxId = 10;
const unsigned maxLigne = 4;

class Upgrade {
public:
    Upgrade(unsigned, unsigned);
    std::vector<unsigned> getResource() const;
    unsigned getPrice() const;
    void display() const;
    void Test();

private:
    std::vector<unsigned> resources;  //idUpgrade, idObjN1, numberObjN1, idObjN2, numberObjN2, idObjN3, numberObjN3, idObjN4,  numberObjN4
    unsigned price;
};

#endif

// Forme du fichier  ATTENTION pour que la lecture soit plus simple il faut que les ligne aient le même nombre
// d'élements quitte a les mettres a 0 comme ca simple condition a faire pour verifier si on garde idObjN°_

// idObject, idResourceNb1, nbCopyNb1, idResourceNb2, nbCopyNb2, idResourceNb3, nbCopyNb3, idResourceNb4, nbCopyNb4