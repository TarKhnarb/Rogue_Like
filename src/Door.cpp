#include "Door.h"

/***************
 * Constructor *
 **************/

Door::Door(): open(true){}

/************
 * Get Open *
 ***********/

bool Door::getOpen() const{
    return open;
}

/************
 * Set Open *
 ***********/

void Door::setOpen(bool a){
    open = a;
}
