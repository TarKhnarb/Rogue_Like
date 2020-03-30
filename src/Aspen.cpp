#include "menu.h"
#include <iostream>
#include <istream>

int main(){

    menu jeu = menu();

    jeu.logic();

    /*
    Donjon test = Donjon(4);
    std::cout << std::endl;
    std::cout << test.RoomCoordToChar(10, 10); // centre
    std::cout << test.RoomCoordToChar(11, 10); // south
    std::cout << test.RoomCoordToChar(10, 11); // east
    std::cout << test.RoomCoordToChar(10, 9); // Weast
    std::cout << test.RoomCoordToChar(9, 10); // north*/

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


	Stage d;
	unsigned stage = 0;
	d.generate(stage);
	d.affectRoomTypeMonsterObject();
	std::cout << d.getSeed() << std::endl;
	std::cout << d;
*/
	//std::cout << d.getStage() << std::endl;*/

	return 0;
}
