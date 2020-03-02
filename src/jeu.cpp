//#include "Donjon.h"
#include "Room.h"
#include <iostream>

int main(){

    Room test;

    switch (test.getType()){
        case roomType::Start: std::cout << "Common" << std::endl;
            break;
        default: std::cout << "autre" << std::endl;
            break;
    };


     //test.getType();


    return 0;
}
