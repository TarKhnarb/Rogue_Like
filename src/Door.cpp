#include "Door.h"

Door::Door(){
    key = false;
    open = false;
}

bool Door::getKey() const{
    return key;
}

bool Door::getOpen() const{
    return open;
}

void Door::setOpen(bool a){
    open = a;
}
