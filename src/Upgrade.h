#ifndef UPGRADE_H
#define UPGRADE_H

const unsigned maxUpgrades = 10;

class Upgrade {
public:
    Upgrade* getResource(unsigned) const;
    unsigned getPrice(unsigned) const;

private:
    unsigned idUpgrade; //idObject
    unsigned price;
    unsigned idObjN1;
    unsigned numberObjN1;
    unsigned idObjN2;
    unsigned numberObjN2;
    unsigned idObjN3;
    unsigned numberObjN3;
    unsigned idObjN4;
    unsigned numberObjN4;

};

#endif

// Forme du fichier  ATTENTION pour que la lecture soit plus simple il faut que les ligne aient le même nombre
// d'élements quitte a les mettres a 0 comme ca simple condition a faire pour verifier si on garde idObjN°_

// idObject, price, idObjN°1, numberObjN°1, idObjN°2, numberObjN°2, idObjN°3, numberObjN°3, idObjN°4, numberObjN°4