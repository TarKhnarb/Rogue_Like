#include <vector>
#include "game.h"
#include "menu.h"

#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"
//verify si c'est ok pour les dependance

void game::gameLoop(){
    initMonster();
    //change position x et y de aspen
    bool game=true;
    while(game){
        displayMap();
        playerLogic();
        updateProjectile();
    }
    menu::logic();
}

void game::displayMap() { //on display le player et les monstre dans la meme procedure
    //recup the 2D tbl made in stage.cpp
    //re-init lorsque player passe la porte
    //on appelle le tbl de monstre ici
    for(unsigned i=0;i<27;++i){
        for(unsigned j=0;j<27;++j){

        }
    }
}

void game::initMonster(){
    for(unsigned i=0;i<3;++i){
        Entity m(10,10,1);
        monsterArray.push_back(m);
    }
}

//inside loop
void game::playerLogic(){
        int c;
        c = win.getCh();
        switch (c) {
            case 'e':
                //escape key >> return to menu
                game=false;
                break;
            case 'z':
                //move the player
                //ASPEN.moveEntity(0,-10)
                break;
            case 'q':
                //ASPEN.moveEntity(-10,0)
                break;
            case 's':
                //ASPEN.moveEntity(0,10)
                break;
            case 'd':
                //ASPEN.moveEntity(10,0)
                break;
            case 'c':
                shoot();
                break;
        }
        updateProjectile();
}
*/
void game::shoot(){
    Projectile p(ASPEN.pos->getPosition(true),ASPEN.pos->getPosition(false),Aspen->getOrientation,0);
    projectileArray.push(p);
}

void game::updateProjectile() {
    for(unsigned i=0;i<projectileArray.size();++i){
        if(projectileArray[i].getProjectilePosition(true) < 0  ||
           projectileArray[i].getProjectilePosition(true) > 27 ||
           projectileArray[i].getProjectilePosition(false) < 0  ||
           projectileArray[i].getProjectilePosition(false) > 27){
            projectileArray[i].runsIntoWall();
        }
    }

    for(unsigned i=0;i<projectileArray[i].size()) {
        projectileArray[i].updateProjectilePosition();
    }
}

