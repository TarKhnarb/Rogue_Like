#include "Door.h"

Door::Door(){
    key = false;
    open = false;
}

Door::Door(bool k, bool o) {
    key = k;
    open = o;
}

bool Door::getKey() const{
    return key;
}

void Door::setKey(bool k) {
    key = k;
}

bool Door::getOpen() const{
    return open;
}

void Door::setOpen(bool a){
    open = a;
}
