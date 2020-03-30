#include <vector>
#include <iostream>
#include "Position.h"
#include "Objects.h"
#include "Projectile.h"

const int numberTest = 10;
unsigned numberSuccess=0;
bool success=false;


/* Position regression test */
std::vector<unsigned> arrayPosition;
std::vector<unsigned> arrayTest;
for(unsigned i=0;i<numberTest;++i){
    Position pos(i,i);
    arrayPosition.pus_back(pos);
    pos.setPosition(i+i,i+i);
    arrayTest.pus_back(pos);
}
    delete pos;

for(unsigned i=0;i<arrayPosition.size();++i){
    arrayPosition[i].move(i,i);
}

for(unsigned i=0;i<inventory.size();++i){
    if(arrayPosition[i].getPosition(true) == arrayTest[i].getPosition(true) &&
        arrayPosition[i].getPosition(false) == arrayTest[i].getPosition(false)){
        numberSuccess++;
    }
}
arrayPosition.clear();
arrayTest.clear();

if(numberTest == numberSuccess){
    std::cout << "Position template working" << std::endl;
}
else{
std::cout << "Position template problem" << std::endl;
}

numberSuccess = 0;

/* Object regression test */

Object num1(1);
Object num2(1);


num1.display();
std::cout<<"Do you see anything 1 = yes, 0 = no ?" << std::endl;
cin >> response;

if(num1.getId() == num2.getId() &&
    num1.getType() = num2.getType() &&
    num1.getName() == num2.getName() &&
    num1.getPrice() == num2.getPrice() &&
    num2.getResalePrice() == num2.getResalePrice()){
    success = true;
}

if(success == false)
    std::cout << " There is a problem here with the stats " <<std::endl;

delete num2;
num1.display();
std::cout<<"Can you see anything and do the stats go between 0(min) and 500(max)" <<std::endl;
cin >> response;
if(response)
    std::cout<<"All is right then" << std::endl;
delete num1;

/* Projectile regression test */

Projectile proj(50,50,0,0);

if(proj.getProjectileOrientation != 0)
    std::cout << "Orientation is not correct" <<std::endl;

proj.displayProjectile();
std::cout << "Does anything display 1(yes), 0 (no)?" std::endl;
cin >> response ;
if(reponse != 1)
    std::cout << "Something is wrong then "<< std::endl;

for(unsigned i=0;i<10;++i){
    proj.update();
}
if(proj.getProjectilePosition(true) == 50 &&
    proj.getProjectilePosition(false) == 40){
    std::cout << "Nice !!" <<std::endl;
    }else{
    std::cout << "Problem with update" << std:endl;
    }

proj.runsIntoWall();
if(proj.getSpeedProjectile()== 1  &&
    proj.getProjectileType == 0 &&
    proj.getCollisionNb() == 1){
    std::cout << "No problem here" <<std::endl;
}

delete proj;


