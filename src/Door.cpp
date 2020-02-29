#include "Door.h"

Door::Door(){
    exist = false;
    key = false;
    open = false;
}

void Door::openIt(){
    if(exist) open = true; // Si la porte existe, ouvrir la porte
}

void Door::closeIt(){
    if(exist) open = false; // Si la porte existe, ferme la porte
}

bool Door::getExist(){
    return exist;
}

void Door::setExist(bool a){
    exist = a;
}

bool Door::getKey(){
    return key;
}
void Door::setKey(bool a){
    key = a;
}

bool Door::getOpen(){
    return  open;
}
void Door::setOpen(bool a){
    open = a;
}
