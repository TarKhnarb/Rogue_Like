#include "game.h"

game::game(Entity &aspen):
        donjon (new Donjon(maxStageDonjon)),
        donjonRoom (donjon->RoomCoordToChar(posDonjonX, posDonjonY)), // joueur placé dans la salle de start
        stage (donjon->getCurrentStage()),
        posDonjonX (10),
        posDonjonY (10),
        Aspen (aspen),
        testgame (true){

    Aspen.setPosition(13, 13);
}

Entity game::getAspen() const{
    return Aspen;
}

void game::gameLoop(char input){

    //change position x et y de aspen

    while(testgame){
        std::cout << donjonRoom;
        playerLogic(input);
    }
    //menu::logic(); A appeler dans game !
}

void game::placeCharInRoom(unsigned x, unsigned y, char entity) {
    donjonRoom[y][x] = entity;
}

void game::playerLogic(char pic){

       // pic = win.getCh(); // prend le char tapé sur le clavier
        switch (pic) {
            case 'm': // return to menu
                //escape key >> return to menu
                testgame = false;
                break;

            case 'z': // move the player above
                move(0);
                break;

            case 'q': // move the player left
                move(3);
                break;

            case 's': // move the player below
                move(2);
                break;

            case 'd': // move the player right
                move(1);
                break;

            case '8': // shoot above
                shoot(0);
                break;

            case '4': // shoot left
                shoot(1);
                break;

            case '5': // shoot below
                shoot(2);
                break;

            case '6': // shoot right
                shoot(3);
                break;

            default:
                break;
        }
        updateProjectile();
}

void game::move(unsigned orient) {

    unsigned posx = Aspen.getPosition(true);
    unsigned posy = Aspen.getPosition(false);

    switch (orient){
        case 0:
            if(testCharNothing(posx-1, posy)){
                placeCharInRoom(posx-1, posy, '*');
                placeCharInRoom(posx, posy, ' ');
                Aspen.setPosition(posx-1, posy);
            }
            if(testCharDoor(posx-1, posy)){
                placeCharInRoom(posx, posy, ' ');
                donjonRoom = donjon->RoomCoordToChar(posDonjonX-1, posDonjonY);
                Aspen.setPosition(13, 24); // devant la porte du bas
            }
            if(testCharTrape(posx-1, posy)){
                if(donjon->getStage() < maxStageDonjon){
                    donjon->nextStage();
                    Aspen.setPosition(13, 13);
                }
                else{
                    testgame = false;
                }
            }

            break;

        case 1:
            if(testCharNothing(posx, posy+1)){
                placeCharInRoom(posx, posy+1, '*');
                placeCharInRoom(posx, posy, ' ');
                Aspen.setPosition(posx, posy+1);
            }
            if(testCharDoor(posx, posy+1)){
                placeCharInRoom(posx, posy, ' ');
                donjonRoom = donjon->RoomCoordToChar(posDonjonX, posDonjonY+1);
                Aspen.setPosition(2, 13); // Porte de gauche
            }
            if(testCharTrape(posx, posy+1)){
                if(donjon->getStage() < maxStageDonjon){
                    donjon->nextStage();
                    Aspen.setPosition(13, 13);
                }
                else{
                    testgame = false;
                }
            }
            break;

        case 2:
            if(testCharNothing(posx+1, posy)){
                placeCharInRoom(posx+1, posy, '*');
                placeCharInRoom(posx, posy, ' ');
                Aspen.setPosition(posx+1, posy);
            }
            if(testCharDoor(posx+1, posy)){
                placeCharInRoom(posx, posy, ' ');
                donjonRoom = donjon->RoomCoordToChar(posDonjonX+1, posDonjonY);
                Aspen.setPosition(13, 2); // Porte du haut
            }
            if(testCharTrape(posx+1, posy)){
                if(donjon->getStage() < maxStageDonjon){
                    donjon->nextStage();
                    Aspen.setPosition(13, 13);
                }
                else{
                    testgame = false;
                }}
            break;

        case 3:
            if(testCharNothing(posx, posy-1)){
                placeCharInRoom(posx, posy-1, '*');
                placeCharInRoom(posx, posy, ' ');
                Aspen.setPosition(posx, posy-1);
            }
            if(testCharDoor(posx, posy-1)){
                placeCharInRoom(posx, posy, ' ');
                donjonRoom = donjon->RoomCoordToChar(posDonjonX, posDonjonY-1);
                Aspen.setPosition(24, 13); // porte de droite
            }
            if(testCharTrape(posx, posy-1)){
                if(donjon->getStage() < maxStageDonjon){
                    donjon->nextStage();
                    Aspen.setPosition(13, 13);
                }
                else{
                    testgame = false;
                }
            }
            break;
    }
}

void game::shoot(unsigned orient){
    Projectile proj(Aspen.getPosition(true), Aspen.getPosition(false), orient, 0);
    projectileVector.push_back(proj);
}

char game::coordonateToChar(unsigned x, unsigned y) {
    return donjonRoom[y][x];
}

bool game::testCharNothing(unsigned x, unsigned y) {

    if(coordonateToChar(x, y) == ' ')
        return true;
    else
        return false;
}

bool game::testCharDoor(unsigned x, unsigned y) {
    
    if(coordonateToChar(x, y) == '8')
        return true;
    else
        return false;
}

bool game::testCharTrape(unsigned x, unsigned y) {

    if(coordonateToChar(x, y) == 'T')
        return true;
    else
        return false;
}

void game::updateProjectile() {

    for(unsigned i = 0; i < projectileVector.size(); ++i){

        unsigned posx = projectileVector[i].getProjectilePosition(true);
        unsigned posy = projectileVector[i].getProjectilePosition(false);

        switch(projectileVector[i].getProjectileOrientation()){

            case 0:
                posx--; // Le projectile apparrait pas sur le joueur
                if(testCharNothing(posx-1, posy)){
                    placeCharInRoom(posx-1, posy, '*');
                    placeCharInRoom(posx, posy, ' ');
                    projectileVector[i].update();
                }
                else
                    projectileVector.erase(projectileVector.begin() + i - 1);
                break;

            case 1:
                posy++;
                if(testCharNothing(posx, posy+1)){
                    placeCharInRoom(posx, posy+1, '*');
                    placeCharInRoom(posx, posy, ' ');
                    projectileVector[i].update();
                }
                else
                    projectileVector.erase(projectileVector.begin() + i - 1);
                break;

            case 2:
                posx++;
                if(testCharNothing(posx+1, posy)){
                    placeCharInRoom(posx+1, posy, '*');
                    placeCharInRoom(posx, posy, ' ');
                    projectileVector[i].update();
                }
                else
                    projectileVector.erase(projectileVector.begin() + i - 1);
                break;

            case 3:
                posy--;
                if(testCharNothing(posx, posy-1)){
                    placeCharInRoom(posx, posy-1, '*');
                    placeCharInRoom(posx, posy, ' ');
                    projectileVector[i].update();
                }
                else
                    projectileVector.erase(projectileVector.begin() + i - 1);
                break;

            default:
                break;
        }

    }
}

