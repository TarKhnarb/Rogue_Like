#include "Door.h"

/***************
 * Constructor *
 **************/

Door::Door(){
    key = false;
    open = false;
}

/**************
 * Destructor *
 *************/

Door::Door(bool k, bool o) {
    key = k;
    open = o;
}

/***********
 * Get Key *
 **********/

bool Door::getKey() const{
    return key;
}

/***********
 * Set Key *
 **********/

void Door::setKey(bool k) {
    key = k;
}

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
