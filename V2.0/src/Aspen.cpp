#include <iostream>
#include <istream>

#include "Entity.h"
#include "Donjon.h"
#include "Npc.h"

int main(){
/*
    unsigned stage = 2;

    float x = 0.0, y = 0.0;

    Entity Aspen(x, y);

    Donjon test(stage, Aspen);
    unsigned i = 0, j = 0;

    std::cout << test.getStage();
    std::cout << "Entrer les coords de la salle" << std::endl;
    std::cin >> i >> j;
    test.displayDoors(i, j);

    std::cout << "Entrer les coords de la salle" << std::endl;
    std::cin >> i >> j;
    std::cout << test.getStage();
    test.displayMonsters(i, j);

    unsigned st = 1;
    Stage test(Aspen);
    test.generate(st);
    test.randomObjects(5);
*/
    std::cout << "1" << std::endl;
    unsigned t;
    unsigned choice;
    float x = 0.0, y = 0.0;
    std::cout << "2" << std::endl;
    Entity Aspen(x, y);
    std::cout << "3" << std::endl;
    Aspen.addInventoryObject(58, 11); // id: 58, nb: 11
    Aspen.displayEntity();
    std::cout << "On a ajouté l'obj 58 au nombre de 11"<< std::endl;
    std::cin >> t;

    Npc npc;
    npc.ActionsBlacksmith(Aspen);
    npc.display(Npc::Action::make);
    std::cin >> choice;

    npc.makeBlacksmith(Aspen, choice); //fabrique l'object 11
    Aspen.displayEntity();
    std::cout << "On a fabrique l'obj 11 (a besoin de 1 fois l'obj 58)" << std::endl;
    std::cin >> t;

    Aspen.addInventoryObject(12, 1);
    Aspen.displayEntity();
    std::cout << "On a ajouté l'obj 12 au nombre de 1"<< std::endl;
    std::cin >> t;

    npc.display(Npc::Action::upgrade);
    std::cin >>  choice;
    npc.upgradeBlacksmith(Aspen, choice); //fabrique l'object 11
    Aspen.displayEntity();
    std::cout << "On fabrique l'obj 11 (a besoin de 1 fois l'obj 58)" << std::endl;
    std::cin >> t;

    return 0;
}
