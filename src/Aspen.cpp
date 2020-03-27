#include "Entity.h"
#include <iostream>
#include <vector>
#include "Stage.h"

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
/*
    unsigned pos = 10;
    Entity aspen = Entity(pos, pos);

    aspen.displayEntity();

	*/
	Stage d;
	unsigned stage = 0;
	d.generate(stage);
	d.roomTypeMonsterObjectAffect();
	std::cout << d.getSeed() << std::endl;
	std::cout << d;

	//std::cout << d.getStage() << std::endl;*/

	return 0;
}
