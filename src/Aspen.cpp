#include <iostream>
#include <istream>

#include "Party.h"
#include "Entity.h"
#include "Donjon.h"
#include "Npc.h"
#include "Stage.h"

int main(){
    // TODO remove this loop when Map will be created
    while(true){
        try{
            Party game;
            game.run();
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
