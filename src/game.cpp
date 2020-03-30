#include "game.h"

game::game(const Entity &aspen):
        posDonjonX (10),
        posDonjonY (10),
        donjon (Donjon(maxStageDonjon)),
        donjonRoom (donjon.RoomCoordToChar(posDonjonX, posDonjonY)), // joueur placé dans la salle de start
        stage (donjon.getCurrentStage()),
        Aspen (aspen),
        testgame (true){

    Aspen.setPosition(13, 13);
}

Entity game::getAspen() const{
    return Aspen;
}

void game::gameLoop(char input){

    std::cout << stage;

    //change position x et y de aspen

 //   while(testgame){
        std::cout << donjonRoom;
        playerLogic(input);
   // }
    //menu::logic(); A appeler dans game !
}

void game::placeCharInRoom(unsigned x, unsigned y, char entity) {
    donjonRoom[x][y] = entity;
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

            case 'i': // shoot above
                shoot(0);
                break;

            case 'j': // shoot left
                shoot(3);
                break;

            case 'k': // shoot below
                shoot(2);
                break;

            case 'l': // shoot right
                shoot(1);
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
                posDonjonX--;
                placeCharInRoom(posx, posy, ' ');
                donjonRoom = donjon.RoomCoordToChar(posDonjonX, posDonjonY);
                Aspen.setPosition(24, 13); // devant la porte du bas
                placeCharInRoom(24, 13, '*');
            }
            if(testCharTrape(posx-1, posy)){
                if(donjon.getStage() < maxStageDonjon){
                    donjon.nextStage();
                    posDonjonY = posDonjonX = 10;
                    donjonRoom = donjon.RoomCoordToChar(posDonjonX, posDonjonY);
                    Aspen.setPosition(13, 13);
                    placeCharInRoom(13, 13, '*');
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
                posDonjonY++;
                placeCharInRoom(posx, posy, ' ');
                donjonRoom = donjon.RoomCoordToChar(posDonjonX, posDonjonY);
                Aspen.setPosition(13, 2); // Porte de gauche
                placeCharInRoom(13, 2, '*');
            }
            if(testCharTrape(posx, posy+1)){
                if(donjon.getStage() < maxStageDonjon){
                    donjon.nextStage();
                    posDonjonY = posDonjonX = 10;
                    donjonRoom = donjon.RoomCoordToChar(posDonjonX, posDonjonY);
                    Aspen.setPosition(13, 13);
                    placeCharInRoom(13, 13, '*');
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
                posDonjonX++;
                placeCharInRoom(posx, posy, ' ');
                donjonRoom = donjon.RoomCoordToChar(posDonjonX, posDonjonY);
                Aspen.setPosition(2, 13); // Porte du haut
                placeCharInRoom(2, 13, '*');
            }
            if(testCharTrape(posx+1, posy)){
                if(donjon.getStage() < maxStageDonjon){
                    donjon.nextStage();
                    posDonjonY = posDonjonX = 10;
                    donjonRoom = donjon.RoomCoordToChar(posDonjonX, posDonjonY);
                    Aspen.setPosition(13, 13);
                    placeCharInRoom(13, 13, '*');
                }
                else{
                    testgame = false;
                }
            }
            break;

        case 3:
            if(testCharNothing(posx, posy-1)){
                placeCharInRoom(posx, posy-1, '*');
                placeCharInRoom(posx, posy, ' ');
                Aspen.setPosition(posx, posy-1);
            }
            if(testCharDoor(posx, posy-1)){
                posDonjonY--;
                placeCharInRoom(posx, posy, ' ');
                donjonRoom = donjon.RoomCoordToChar(posDonjonX, posDonjonY);
                Aspen.setPosition(13, 24); // porte de droite
                placeCharInRoom(13, 24, '*');
            }
            if(testCharTrape(posx, posy-1)){
                if(donjon.getStage() < maxStageDonjon){
                    donjon.nextStage();
                    posDonjonY = posDonjonX = 10;
                    donjonRoom = donjon.RoomCoordToChar(posDonjonX, posDonjonY);
                    Aspen.setPosition(13, 13);
                    placeCharInRoom(13, 13, '*');
                }
                else{
                    testgame = false;
                }
            }
            break;
    }
}

void game::shoot(unsigned orient){

    projectileVector.push_back(new Projectile(Aspen.getPosition(true), Aspen.getPosition(false), orient, 0));
}

char game::coordonateToChar(unsigned x, unsigned y) {
    return donjonRoom[x][y];
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
    for(unsigned i = 0; i < projectileVector.size(); ++i) {
        if(projectileVector[i]){
            unsigned posx = projectileVector[i]->getProjectilePosition(true);
            unsigned posy = projectileVector[i]->getProjectilePosition(false);

            switch (projectileVector[i]->getProjectileOrientation()) {

                case 0:
                    posx--;
                    if (testCharNothing(posx-1, posy)) {
                        placeCharInRoom(posx-1, posy, 'i');
                        placeCharInRoom(posx, posy, ' ');
                        projectileVector[i]->update();
                    }
                    else{
                        placeCharInRoom(posx, posy, ' ');
                        projectileVector.erase(projectileVector.begin() + i);
                    }
                    break;

                case 1:
                    posy++;
                    if (testCharNothing(posx, posy+1)) {
                        placeCharInRoom(posx, posy+1, 'i');
                        placeCharInRoom(posx, posy, ' ');
                        projectileVector[i]->update();
                    }
                    else{
                        placeCharInRoom(posx, posy, ' ');
                        projectileVector.erase(projectileVector.begin() + i);
                    }
                    break;

                case 2:
                    posx++;
                    if (testCharNothing(posx+1, posy)) {
                        placeCharInRoom(posx+1, posy, 'i');
                        placeCharInRoom(posx, posy, ' ');
                        projectileVector[i]->update();
                    }
                    else{
                        placeCharInRoom(posx, posy, ' ');
                        projectileVector.erase(projectileVector.begin() + i);
                    }
                    break;

                case 3:
                    posy--; // Le projectile apparrait pas sur le joueur
                    if (testCharNothing(posx, posy-1)) {
                        placeCharInRoom(posx, posy-1, 'i');
                        placeCharInRoom(posx, posy, ' ');
                        projectileVector[i]->update();
                    }
                    else{
                        placeCharInRoom(posx, posy, ' ');
                        projectileVector.erase(projectileVector.begin() + i);
                    }
                    break;

                default:
                    break;
            }
        }
    }
}

bool game::getTestgame() {
    return testgame;
}

