#include "map.h"

int main(){

    while(true){
        try{
            map test;
            test.run();
        }
        catch (std::range_error& err){ // player finished the dungeon or dies
            std::cerr << err.what() << std::endl;
            continue;
        }
        catch (std::runtime_error& err){ // failed to load something
            std::cerr << err.what() << std::endl;
            break;
        }

        break;
    }

    return 0;
}