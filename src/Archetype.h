#ifndef GAME_ARCHETYPE_H
#define GAME_ARCHETYPE_H
// Rocher 40x40
// Portes : N/S : 80x60 / EW : 60x80
// Encadrement Portes : N/S : 120x80
// Image 1280x720

// Walls : { { (0), (1), (2), (3)}, ... } : (0): xMin, (1): yMin, (2): xMax, (3): yMax
// DoorPOSITION : {{0}, {1}} : (0): encadrement, (1): porte O/F
// MonsterROOM : Spawnpoint of mosters
// RocksROOM : Set position for rocks
// ChestROOM : Set position for (the) chest


struct Archetype{

        // Map

    const float wallMap[25][4] =
            {{886, 545, 83, 295}, {885, 481, 215, 94}, {985, 360, 71, 121}, {1053, 359, 455, 40}, {1445, 359, 473, 168},
             {1341, 559, 174, 26}, {1466, 583, 451, 45}, {1529, 629, 388, 36}, {1652, 665, 185, 355}, {1550, 732, 1689, 798},
             {1543, 879, 210, 156}, {1425, 955, 177, 111}, {1387, 974, 42, 96}, {1061, 1029, 323, 40}, {730, 1006, 445, 23},
             {651, 945, 239, 59}, {660, 655, 77, 297}, {737, 644, 68, 102}, {802, 637, 132, 52}, {820, 760, 66, 57},
             {1194, 694, 63, 57}, {1058, 641, 49, 56}, {1196, 464, 64, 57}, {1216, 864, 67, 57}, {1649, 827, 40, 53}};


        // Inventory
    const float playerInventory[2] = {400, 80};

    const float statInventory[2][2] = {{420, 270}, {525, 270}};

    const float itemBag[10][2] =
            {{665, 91}, {665, 143}, {665, 195}, {665, 247}, {665, 299},
             {785, 91}, {785, 143}, {785, 195}, {785, 247}, {785, 299}};

    const float itemStuff[6][2] =
            {{422, 95}, {422, 150}, {422, 205},
             {557, 95}, {557, 150}, {557, 205}};

    const float inventoryAspen[2] = {485, 115};

    const float chestInventory[2] = {400, 360};

    const float itemChest[20][2] =
            {{431, 377}, {431, 442}, {431, 507}, {431, 572},
             {523, 377}, {523, 442}, {523, 507}, {523, 572},
             {615, 377}, {615, 442}, {615, 507}, {615, 572},
             {707, 377}, {707, 442}, {707, 507}, {707, 572},
             {799, 377}, {799, 442}, {799, 507}, {799, 572}};


        // Player Spawn
    const float PlayerN[2] = {620, 135};
    const float PlayerE[2] = {980, 300};
    const float PlayerS[2] = {620, 450};
    const float PlayerW[2] = {260, 300};

        //__________ Walls __________
    const float Walls[8][4] =
            {{0, 0, 610, 160}, {670, 0, 610, 160}, {1040, 160, 240, 170}, {1040, 390, 240, 330},
             {670, 560, 610, 160}, {240, 560, 370, 160}, {0, 390, 240, 330}, {0, 0, 240, 330}};
        //__________ Doors __________
    const float DoorN[2][2] =
            {{580, 80}, {580, 80}};

    const float DoorE[2][2] =
            {{1040, 300}, {1040, 302}};

    const float DoorS[2][2] =
            {{580, 560}, {580, 560}};

    const float DoorW[2][2] =
            {{160, 300}, {160, 302}};

        //__________ Boss Room __________

    const float MonsterBoss[2] = {640, 360}; // centre de la salle à adapter en fonction des dimensions du boss tiré

        //__________ Room2NS1 __________

    const float Monster2NS1[6][2] =
            {{640, 320}, {640, 400}, {300, 260}, {1000, 460}, {300, 460}, {1000, 260}};

    const float Hole2NS1[28][2] =
            {{360, 160}, {360, 220}, {360, 280}, {360, 340}, {360, 400}, {360, 460}, {360, 520},
             {420, 160}, {420, 220}, {420, 280}, {420, 340}, {420, 400}, {420, 460}, {420, 520},
             {820, 160}, {820, 220}, {820, 280}, {820, 340}, {820, 400}, {820, 460}, {820, 520},
             {880, 160}, {880, 220}, {880, 280}, {880, 340}, {880, 400}, {880, 460}, {880, 520}};

        //__________ Room2NS2 __________

    const float Monster2NS2[6][2] =
            {{640, 320}, {640, 400}, {450, 260}, {850, 460}, {450, 460}, {850, 260}};

        //__________ Room2WE1 __________

    const float Monster2WE1[6][2] =
            {{570, 230}, {710, 510}, {490, 230}, {790, 510}, {530, 310}, {750, 430}};

    const float Rocks2WE1[24][2] =
            {{240, 160}, {240, 200}, {240, 240}, {240, 440}, {240, 480},
             {240, 520}, {280, 160}, {280, 200}, {280, 480}, {280, 520},
             {320, 160}, {320, 520},{1000, 160}, {1000, 200}, {1000, 240},
             {1000, 440}, {1000, 480}, {1000, 520}, {960, 160}, {960, 200},
             {960, 480}, {960, 520}, {920, 160}, {920, 520}};

    const float Hole2WE1[19][2] =
            {{340, 320}, {340, 380}, {400, 380}, {400,440}, {460,440},
             {460, 500}, {520, 500}, {700, 160}, {760, 160}, {760, 220},
             {820, 220}, {820, 280}, {880, 280}, {880,340}, {628, 280},
             {628, 340}, {568, 340}, {688, 340}, {628, 400}};

        //__________ Room2WE2 __________

    const float Monster2WE2[6][2] =
            {{640, 320}, {640, 400}, {450, 260}, {850, 460}, {450, 460}, {850, 260}};

        //__________ Room4NESW1 __________

    const float Monster4NESW1[6][2] =
            {{640, 320}, {640, 400}, {450, 260}, {850, 460}, {450, 460}, {850, 260}};

        //__________ Room4NESW2 __________

    const float Monster4NESW2[6][2] =
            {{640, 320}, {640, 400}, {450, 260}, {850, 460}, {450, 460}, {850, 260}};

    const float Rocks4NESW2[24][2] =
            {{240, 160}, {240, 200}, {240, 240}, {240, 440}, {240, 480},
             {240, 520}, {280, 160}, {280, 200}, {280, 480}, {280, 520},
             {320, 160}, {320, 520},{1000, 160}, {1000, 200}, {1000, 240},
             {1000, 440}, {1000, 480}, {1000, 520}, {960, 160}, {960, 200},
             {960, 480}, {960, 520}, {920, 160}, {920, 520}};

        //__________ Room1N __________

    const float Monster1N[6][2] =
            {{585, 500}, {695, 500}, {420, 360}, {860, 360}, {585, 250}, {695, 250}};

    const float Rocks1N[8][2] =
            {{620, 280}, {580, 300}, {560, 340}, {580, 380}, {620, 400},
             {660, 380}, {680, 340}, {660, 300}};

    const float Chest1N[2] =
            {620, 340};

    const float Hole1N[20][2] =
            {{300, 160}, {360, 160}, {300, 220}, {240, 220}, {240, 280},
             {240, 380}, {240, 440}, {300, 440}, {300, 500}, {360, 500},
             {860, 160}, {920, 160}, {920, 220}, {980, 220}, {980, 280},
             {980, 380}, {980, 440}, {920, 440}, {920, 500}, {860, 500}};

        //__________ Room1E __________

    const float Monster1E[6][2] =
            {{300, 160}, {300, 460}, {640, 230}, {640, 400}, {850, 260}, {850, 460}};

    const float Chest1E[2] =
            {250, 340};

        //__________ Room1S __________

    const float Monster1S[6][2] =
            {{360, 200}, {920, 200}, {480, 200}, {800, 200}, {390, 435}, {890, 435}};

    const float Rocks1S[16][2] =
            {{240, 360}, {240, 400}, {280, 400}, {240, 440}, {280, 440},
             {240, 480}, {280, 480}, {240, 520}, {1000, 360}, {960, 400},
             {1000, 400}, {960, 440}, {1000, 440}, {960, 480}, {1000, 480},
             {1000, 520}};

    const float Chest1S[2] =
            {620, 160};

    const float Hole1S[22][2] =
            {{240, 240}, {300, 240}, {360, 240}, {420, 240}, {480, 240},
             {540, 240}, {680, 240}, {740, 240}, {800, 240}, {860, 240},
             {920, 240}, {980, 240}, {240, 300}, {300, 300}, {360, 300},
             {420, 300}, {480, 300}, {740, 300}, {800, 300}, {860, 300},
             {920, 300}, {980, 300}};

        //__________ Room1W __________

    const float Monster1W[6][2] =
            {{500, 220}, {500, 500}, {780, 220}, {780, 500}, {560, 360}, {720, 360}};

    const float Rocks1W[31][2] =
            {{600, 160}, {640, 160}, {560, 200}, {600, 200}, {640, 200},
             {680, 200}, {560, 240}, {600, 240}, {640, 240}, {680, 240},
             {600, 280}, {640, 280}, {600, 520}, {640, 520}, {560, 480},
             {600, 480}, {640, 480}, {680, 480}, {560, 440}, {600, 440},
             {640, 440}, {680, 440}, {600, 400}, {640, 400}, {1000, 260},
             {960, 300}, {1000, 300}, {940, 340}, {960, 380}, {1000, 380},
             {1000, 420}};

    const float Chest1W[2] =
            {1000, 340};

    const float Hole1W[16][2] =
            {{240, 160}, {300, 160}, {300, 220}, {360, 220},
             {860, 220}, {920, 220}, {920, 160}, {980, 160},
             {240, 500}, {300, 500}, {300, 440}, {360, 440},
             {860, 440}, {920, 440}, {920, 500}, {980, 500}};

        //__________ Room3NES __________

    const float Monster3NES[6][2] =
            {{640, 320}, {640, 400}, {300, 260}, {300, 460}, {850, 260}, {850, 460}};

        //__________ Room3ESW __________

    const float Monster3ESW[6][2] =
            {{320, 220}, {960, 220}, {320, 500}, {960, 500}, {550, 400}, {730, 400}};

    const float Chest3ESW[2] =
            {620, 160};

    const float Hole3ESW[12][2] =
            {{400, 160}, {460, 160}, {460, 220}, {520, 220},
             {520, 280}, {580, 280}, {640, 280}, {700, 280},
             {700, 220}, {760, 220}, {760, 160}, {820, 160}};
        //__________ Room3NSW __________

    const float Monster3NSW[6][2] =
            {{640, 320}, {640, 400}, {850, 260}, {850, 460}, {450, 260}, {450, 460}};

    const float Rocks3NSW[11][2] =
            {{1000, 220}, {960, 260}, {920, 300}, {1000, 300}, {880, 340},
             {960, 340}, {1000, 340}, {920, 380}, {1000, 380}, {960, 420},
             {1000, 460}};

        //__________ Room3NEW __________

    const float Monster3NEW[6][2] =
            {{540, 520}, {740, 520}, {360, 240}, {920, 240}, {360, 520}, {920, 520}};

    const float Rocks3NEW [7][2] =
            {{540, 420}, {580, 420}, {620, 420}, {660, 420}, {700, 420},
             {600, 380}, {640, 380}};

    const float Hole3NEW[10][2] =
            {{240, 420}, {300, 420}, {360, 420}, {420, 420}, {480, 420},
             {740, 420}, {800, 420}, {860, 420}, {920, 420}, {980, 420}};
};
#endif
