#include "Door.h"

Door::Door(){
    exist = false;
    key = false;
    open = false;
}

void Door::openIt(){
    if(! key && exist) open = true; // Si la porte ne necessite pas de cle et existe ouvrir la porte
}