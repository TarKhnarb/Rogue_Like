#include <iostream>
#include <istream>

#include "Party.h"
//#include "Entity.h"
//#include "Donjon.h"
//#include "Npc.h"
#include "Stage.h"

/*int main(){
    Chest chest;

    Stage test;
    test.gererate()
}*/

int main(){
    Party game;
    game.run();
}

/*int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFMLApplication");
    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(100.f, 100.f);
    shape.setFillColor(sf::Color::Cyan);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
}*/
/*
int main(){

    unsigned stage = 0;
    unsigned maxStage = 5;

    float x = 0.0, y = 0.0;

    Entity Aspen(x, y);

    Donjon test(5, Aspen);
    std::cout << std::endl;
    std::cout << std::endl;
    test.nextStage();
    std::cout << test.getCurrentStage();

    //std::cout << test.getStage();
    std::cout << "Entrer les coords de la salle" << std::endl;
    std::cin >> i >> j;
    test.displayDoors(i, j);

    test.displayMonsters(i, j);

    test.displayRocks(i, j);

    test.displayChest(i, j);

    unsigned st = 1;
    Stage test(Aspen);
    test.generate(st);
    test.randomObjects(5);

    std::cout << "1" << std::endl;
    unsigned t;
    unsigned choice;
    float x = 0.0, y = 0.0;
    std::cout << "2" << std::endl;
    Entity Aspen(x, y);
    std::cout << "3" << std::endl;
    Aspen.addInventoryObject(58, 6); // id: 58, nb: 11
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
}*/
