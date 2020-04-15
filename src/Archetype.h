#ifndef GAME_ARCHETYPE_H
#define GAME_ARCHETYPE_H
// Rocher 40x40
// Portes : N/S : 80x60 / EW : 60x80
// Encadrement Portes : N/S : 120x80
// Image 1280x720

// DoorPOSITION : {{0}, {1}} : (0): encadrement, (1) : porte O/F
// MonsterROOM : Spawnpoint of mosters
// RocksROOM : Set position for rocks
// ChestROOM : Set position for (the) chest

    //__________ Doors __________

float DoorN[2][2] = 
	    {{580, 80}, {600, 100}};

float DoorE[2][2] = 
	    {{1040, 300}, {1040, 320}};

float DoorS[2][2] = 
	    {{580, 560}, {600, 560}};

float DoorW[2][2] = 
	    {{180, 300}, {200, 320}};

    //__________ Boss Room __________
        
float MonsterBoss[2] =
	    {640, 360}; // centre de la salle à adapter en fonction des dimensions du boss tiré
	    
    //__________ Room2NS1 __________

float Monster2NS1[6][2] = 
	    {{640, 320}, {640, 400}, {450, 260}, {850, 460}, {450, 460}, {850, 260}};

    //__________ Room2NS2 __________
        
float Monster2NS2[6][2] = 
	    {{640, 320}, {640, 400}, {450, 260}, {850, 460}, {450, 460}, {850, 260}};

    //__________ Room2WE1 __________
        
float Monster2WE1[6][2] = 
	    {{570, 230}, {710, 510}, {490, 230}, {790, 510}, {530, 310}, {750, 430}};

float Rocks2WE1[24][2] = 
    	{{240, 160}, {240, 200}, {240, 240}, {240, 440}, {240, 480}, 
	    {240, 520}, {280, 160}, {280, 200}, {280, 480}, {280, 520},
	    {320, 160}, {320, 520},{1000, 160}, {1000, 200}, {1000, 240},
	    {1000, 440}, {1000, 480}, {1000, 520}, {960, 160}, {960, 200},
	    {960, 480}, {960, 520}, {920, 160}, {920, 520}};
    
    //__________ Room2WE2 __________
        
float Monster2WE2[6][2] =
	    {{640, 320}, {640, 400}, {450, 260}, {850, 460}, {450, 460}, {850, 260}};

    //__________ Room4NESW1 __________
        
float Monster4NESW1[6][2] =
	    {{640, 320}, {640, 400}, {450, 260}, {850, 460}, {450, 460}, {850, 260}};

    //__________ Room4NESW2 __________
        
float Monster4NESW2[6][2] =
	    {{640, 320}, {640, 400}, {450, 260}, {850, 460}, {450, 460}, {850, 260}};

float Rocks4NESW2[24][2] = 
    	{{240, 160}, {240, 200}, {240, 240}, {240, 440}, {240, 480}, 
	    {240, 520}, {280, 160}, {280, 200}, {280, 480}, {280, 520},
	    {320, 160}, {320, 520},{1000, 160}, {1000, 200}, {1000, 240},
	    {1000, 440}, {1000, 480}, {1000, 520}, {960, 160}, {960, 200},
	    {960, 480}, {960, 520}, {920, 160}, {920, 520}};
        
    //__________ Room1N __________

float Monster1N[6][2] = 
	    {{585, 500}, {695, 500}, {420, 360}, {860, 360}, {585, 250}, {695, 250}};

float Rocks1N[8][2] =
   	    {{620, 280}, {580, 300}, {560, 340}, {580, 380}, {620, 400},
	    {660, 380}, {680, 340}, {660, 300}};
    
float Chest1N[2] = 
	    {620, 340};
        
    //__________ Room1E __________        

float Monster1E[6][2] = 
	    {{300, 160}, {300, 460}, {640, 230}, {640, 400}, {850, 260}, {850, 460}};

float Chest1E[2] = 
	    {240, 340};
        
    //__________ Room1S __________

float Monster1S[6][2] = 
	    {{360, 200}, {920, 200}, {480, 200}, {800, 200}, {390, 435}, {890, 435}};

float Rocks1S[16][2] = 
    	{{240, 340}, {240, 360}, {280, 400}, {240, 440}, {280, 440}, 
	    {240, 480}, {280, 480}, {240, 520}, {1000, 340}, {960, 360},
	    {1000, 400}, {960, 440}, {1000, 440}, {960, 480}, {1000, 480},
	    {1000, 520}};

float Chest1S[2] =
        {620, 160};
        
    //__________ Room1W __________

float Monster1W[6][2] = 
	    {{500, 220}, {500, 500}, {780, 220}, {780, 500}, {560, 360}, {720, 360}};

float Rocks1W[31][2] =
    	{{600, 160}, {640, 160}, {560, 200}, {600, 200}, {640, 200}, 
	    {680, 200}, {560, 240}, {600, 240}, {640, 240}, {680, 240},
	    {600, 280}, {640, 280}, {600, 520}, {640, 520}, {560, 480},
	    {600, 480}, {640, 480}, {680, 480}, {560, 440}, {600, 440},
	    {640, 440}, {680, 440}, {600, 400}, {640, 400}, {1000, 260},
	    {960, 300}, {1000, 300}, {940, 340}, {960, 380}, {1000, 380},
	    {1000, 420}};

float Chest1W[2] = 
	    {1000, 340};

    //__________ Room3NES __________
        
float Monster3NES[6][2] = 
	    {{640, 320}, {640, 400}, {300, 260}, {300, 460}, {850, 260}, {850, 460}};

    //__________ Room3ESW __________
        
float Monster3ESW[6][2] = 
	    {{320, 220}, {960, 220}, {320, 500}, {960, 500}, {550, 400}, {730, 400}};

float Chest3ESW[2] = 
	    {620, 160};
        
    //__________ Room3NSW __________
        
float Monster3NSW[6][2] = 
	    {{640, 320}, {640, 400}, {850, 260}, {850, 460}, {450, 260}, {450, 460}};

float Rocks3NSW[11][2] = 
    	{{1000, 260}, {960, 300}, {920, 340}, {1000, 340}, {880, 380}, 
	    {960, 380}, {1000, 380}, {920, 420}, {1000, 420}, {960, 460},
	    {1000, 500}};

    //__________ Room3NEW __________
        
float Monster3NEW[6][2] = 
	    {{540, 520}, {740, 520}, {360, 240}, {920, 240}, {360, 520}, {920, 520}};
    
float Rocks3NEW [7][2] = 
    	{{540, 420}, {580, 420}, {620, 420}, {660, 420}, {700, 420}, 
	    {600, 380}, {640, 380}};
#endif