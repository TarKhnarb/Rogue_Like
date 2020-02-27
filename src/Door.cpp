#include "Door.h"

Door::Door(){
    exist = false;
    key = false;
    open = false;
}

void Door::openIt(){
    if(! key) open = true;
}