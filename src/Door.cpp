#include "Door.h"

Door::Door(){
    key = false;
    open = false;
}

bool Door::getKey(){
    return key;
}

bool Door::getOpen(){
    return open;
}
void Door::setOpen(bool a){
    open = a;
}
