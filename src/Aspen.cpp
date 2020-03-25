#include "Entity.h"
#include <iostream>
#include <vector>

void AfficheEntityStats(std::vector<int> stats){

    std::cout << "Entity Stats :" << std::endl;
    for(unsigned i = 0; i < stats.size(); ++i){
        switch (i){
            case 0:
                std::cout << "      fly          : " << stats.at(i) << std::endl;
                break;

            case 1:
                std::cout << "      attack       : " << stats.at(i) << std::endl;
                break;

            case 2:
                std::cout << "      attackSpeed  : " << stats.at(i) << std::endl;
                break;

            case 3:
                std::cout << "      hp           : " << stats.at(i) << std::endl;
                break;

            case 4:
                std::cout << "      defence      : " << stats.at(i) << std::endl;
                break;

            case 5:
                std::cout << "      speed        : " << stats.at(i) << std::endl;
                break;

            default:
                break;
        }
    }
}

int main(){

/*    unsigned addObj = 0;
    Inventory test = Inventory(1, 10);
    AfficheEntityStats(test.getAllEntityStats());

    test.addObjectId(5, 1, addObj);
    test.displayInventory();

    test.equipObjectIndex(4);
    test.displayInventory();
    test.displayEquipment();
    AfficheEntityStats(test.getAllEntityStats());*/

    unsigned pos = 10;
    Entity aspen = Entity(pos, pos);

    aspen.displayEntity();

	
/*	Stage d;
	
	d.generate();
	std::cout << d.getSeed() << std::endl;
	std::cout << d;

	//std::cout << d.getStage() << std::endl;*/

	return 0;
}
