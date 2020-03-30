#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include "Projectile.h"
#include "Donjon.h"

#include <iostream>
#include <vector>
#include <array>

const unsigned maxStageDonjon = 2;

class game {
public :

    game() = default;
    game(const Entity&);

    Entity getAspen() const;

    void gameLoop(char);
    void playerLogic(char);
    void initMap();

    void initMonster();

    void move(unsigned);

    void shoot(unsigned); // En fonction de l'orientation
    void updateProjectile();

private :

    char coordonateToChar(unsigned, unsigned);
    bool testProjectileDirection(unsigned, unsigned); // Renvoie vrai seulement si les coord rentrées (course du projectile) ne rencontrent pas de rocher, mur ou portes

    bool testCharNothing(unsigned, unsigned); // idem que projectile, seul difference les portes nous font passer à la salle d'après
    bool testCharDoor(unsigned, unsigned);
    bool testCharTrape(unsigned, unsigned);

    void placeCharInRoom(unsigned, unsigned, char);

private:

    std::vector<Projectile> projectileVector;

    Donjon donjon;
    std::array< std::array<char, 27>, 27> donjonRoom;
    Stage *stage;

    unsigned posDonjonX;
    unsigned posDonjonY;

    Entity Aspen;
    bool testgame;
};

#endif
