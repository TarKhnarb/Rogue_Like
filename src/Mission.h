#ifndef _MISSION_H
#define _MISSION_H

#include "Entity.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Mission {
    enum Type {
        obtain, //achète, trouve
        step, //faire les quetes précédantes pour pouvoir completer celles qui suivent
    };

    enum TypeObtain {
        object,
        loot,
        potion,
        upgrade,
        specific,
        nullO,
    };

public:
    Mission(unsigned);

    void update(Entity* ,Mission,Mission);

    void isComplete() const;

    bool getComplete() const;

    void updateTypeObtain(Entity*);

private:
    std::string returnCsvItem(std::istringstream &);
    unsigned returnCsvItemSTOI(std::istringstream &);

    unsigned idQuest;
    std::string Quest;

    Type typeQuest;
    TypeObtain typeObtainQuest;
    unsigned nbCopyORid;
    unsigned nbCopyObtain;


    bool Complete;

    //bool Active;
};




#endif //MISSION_H




/* idee :
Entity.cpp

 bool Entity::isDead() {
    return (life==0);
}

void Entity::setLife(unsigned d)
{
    life = d;
}
 Entity.h

    bool isDead();

    void setLife(unsigned);
_____________________
 main

    std::cout << "coucou" << std::endl;
    float y = 1.0;
    Entity hero(y,y);
    std::cout << "enrevoir" << std::endl;
    hero.setLife(1);
    std::cout << hero.isDead();
    hero.setLife(0);
    std::cout << hero.isDead();


    Mission mis(1);
    mis.isComplete();
    mis.setComplete(true);
    Mission mis2(2);
    mis2.isComplete();
    mis2.setComplete(true);
    mis.isComplete();
    mis2.isComplete();

    mis.Upgrade(hero,mis,mis);
    mis.isComplete();
   std::cout << std::endl;
   hero.buyObject(17,1);
   hero.displayEntity();
   mis.Upgrade(hero,mis,mis);
    hero.sellObject(17,1);
   mis.isComplete();
   std::cout << std::endl;


    Mission mis2(2);
    hero.displayEntity();
    mis2.Upgrade(hero,mis,mis2);
    mis2.isComplete();
    std::cout << std::endl;
    hero.buyObject(48,1);
    hero.displayEntity();
    mis2.Upgrade(hero,mis,mis2);
    hero.sellObject(48,1);
    mis2.isComplete();
    std::cout << std::endl;


    Mission mis3(3);
    mis3.isComplete();
    std::cout << std::endl;
    mis3.Upgrade(hero,mis,mis2);
    mis3.isComplete();
    std::cout << std::endl;

Mission mis4(4);
mis4.isComplete();
std::cout << std::endl;
mis4.Upgrade(hero,mis4,mis4);
mis4.isComplete();
std::cout << std::endl;


    Mission mis5(5);
    mis5.Upgrade(hero,mis,mis2);


 */


