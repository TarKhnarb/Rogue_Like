#include "Party.h"

Party::Party():
        posDonjon(10, 10),
        posAspen(620, 310),
        Aspen (posAspen.getPosition(true), posAspen.getPosition(false)),
        donjon(stageNumber, Aspen),
        mWindow(sf::VideoMode(1280, 720), "Aspen's Adventure"){


    loadTextures(); // On charge les textures

    loadSprites("RoomStart"); // On charge la map de start
    loadSprites("Frame"); // on charge les encadrements de porte

    loadRectangleShape("ChestCloseN");
    loadRectangleShape("ChestCloseE");
    loadRectangleShape("ChestCloseS");
    loadRectangleShape("ChestCloseW");

    loadRectangleShape("Rock1");
    loadRectangleShape("Rock2");
    loadRectangleShape("Rock3");

    loadRectangleShape("DoorOpenN");
    loadRectangleShape("DoorOpenE");
    loadRectangleShape("DoorOpenS");
    loadRectangleShape("DoorOpenW");

    loadRectangleShape("DoorCloseN");
    loadRectangleShape("DoorCloseE");
    loadRectangleShape("DoorCloseS");
    loadRectangleShape("DoorCloseW");

    loadRectangleShape("Trap");

    scroll.loadFromFile("data/Font/verdana.ttf"); // charge le police d'écriture verdana
    objectsFont.loadFromFile("data/Font/verdana.ttf");
	statsFont.loadFromFile("data/Font/verdana.ttf");

    loadAnimation();
    
    Aspen.addInventoryObject(60, 20); // monsterLoot
	Aspen.addInventoryObject(47, 1); // potion
	Aspen.addInventoryObject(11); // helmet
    Aspen.addInventoryObject(30); // boots
    
	rocksCollider.setStyle(Style::Separated);
    setInventoryItem();
	reloadRoom();
}

Party::~Party(){
    for(auto &t : textures){
		if (t.second)
			delete t.second;
        t.second = nullptr;
    }

    for(auto &r : rectangleShapes){
        if(r.second)
            delete r.second;
        r.second = nullptr;
    }
}

void Party::run(){

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f / 30.f);

    while (mWindow.isOpen()){
		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > TimePerFrame){
			timeSinceLastUpdate -= TimePerFrame;
			
			if(!inventoryOpen){ // game state
				processEvents();
				update(TimePerFrame);
                
                if (inventoryOpen) // late update
                    updateInventory();
			}
			else if (!scrollingMenuOpen){ // inventory state
				updateInventory();
                
                if (scrollingMenuOpen) // late update
                    updateScrollingMenu();
			}
			else if (!moveObjectOpen){ // srolling menu state
                updateScrollingMenu();
                
                if (moveObjectOpen) // late update
                    updateMoveObject();
            }
            else{ // move object state
                updateMoveObject();
            }
		}
		
        render();
    }
}

void Party::loadTextures(){ // load dans le constructeur
        // Entity
            //Aspen
    sf::Texture* texture(new sf::Texture ());
    texture->loadFromFile("data/Textures/Entity/AspenBack.png");
    textures.emplace("AspenBack", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenFront.png");
    textures.emplace("AspenFront", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenLeft.png");
    textures.emplace("AspenLeft", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenRight.png");
    textures.emplace("AspenRight", std::move(texture));

        // Room
            // Start/Boss
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Start.jpg");
    textures.emplace("RoomStart", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Boss.jpg");
    textures.emplace("RoomBoss", std::move(texture));

            // 1 Door
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room1E.jpg");
    textures.emplace("Room1E", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room1N.jpg");
    textures.emplace("Room1N", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room1S.jpg");
    textures.emplace("Room1S", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room1W.jpg");
    textures.emplace("Room1W", std::move(texture));

            // 2 Doors
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room2NS1.jpg");
    textures.emplace("Room2NS1", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room2NS2.jpg");
    textures.emplace("Room2NS2", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room2WE1.jpg");
    textures.emplace("Room2WE1", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room2WE2.jpg");
    textures.emplace("Room2WE2", std::move(texture));

            // 3 Doors
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room3ESW.jpg");
    textures.emplace("Room3ESW", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room3NES.jpg");
    textures.emplace("Room3NES", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room3NEW.jpg");
    textures.emplace("Room3NEW", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room3NSW.jpg");
    textures.emplace("Room3NSW", std::move(texture));

            // 4 Doors
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room4NESW1.jpg");
    textures.emplace("Room4NESW1", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room4NESW2.jpg");
    textures.emplace("Room4NESW2", std::move(texture));

        // Rocks
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Rock/Rock1.png");
    textures.emplace("Rock1", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Rock/Rock2.png");
    textures.emplace("Rock2", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Rock/Rock3.png");
    textures.emplace("Rock3", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Rock/RockBreak.png");
    textures.emplace("RockBreak", std::move(texture));

        // Frame
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Frame/FrameE.png");
    textures.emplace("FrameE", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Frame/FrameN.png");
    textures.emplace("FrameN", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Frame/FrameS.png");
    textures.emplace("FrameS", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Frame/FrameW.png");
    textures.emplace("FrameW", std::move(texture));

        //  Door
            // Open
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Open/DoorOpenE.png");
    textures.emplace("DoorOpenE", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Open/DoorOpenN.png");
    textures.emplace("DoorOpenN", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Open/DoorOpenS.png");
    textures.emplace("DoorOpenS", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Open/DoorOpenW.png");
    textures.emplace("DoorOpenW", std::move(texture));

            // Close
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Close/DoorCloseE.png");
    textures.emplace("DoorCloseE", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Close/DoorCloseN.png");
    textures.emplace("DoorCloseN", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Close/DoorCloseS.png");
    textures.emplace("DoorCloseS", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Close/DoorCloseW.png");
    textures.emplace("DoorCloseW", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Trap.png");
    textures.emplace("Trap", std::move(texture));

        // Chest
            // Close
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Close/ChestCloseE.png");
    textures.emplace("ChestCloseE", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Close/ChestCloseN.png");
    textures.emplace("ChestCloseN", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Close/ChestCloseS.png");
    textures.emplace("ChestCloseS", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Close/ChestCloseW.png");
    textures.emplace("ChestCloseW", std::move(texture));

        // Open
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Open/ChestOpenE.png");
    textures.emplace("ChestOpenE", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Open/ChestOpenN.png");
    textures.emplace("ChestOpenN", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Open/ChestOpenS.png");
    textures.emplace("ChestOpenS", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Open/ChestOpenW.png");
    textures.emplace("ChestOpenW", std::move(texture));

        // Inventory
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Inventory/ChestInventory.png");
    textures.emplace("ChestInventory", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Inventory/PlayerInventory.png");
    textures.emplace("PlayerInventory", std::move(texture));
}

sf::Texture* Party::getTexture(const std::string& nameText){ // récupere un etexture quand on en a besoin
    auto found = textures.find(nameText);
    if(found == textures.end())
        throw std::runtime_error ("Party::getTexture(const std::string&) - Aucune texture de ce nom " + nameText);

    return found->second; // ( si pas * on retourne un pointeur de texture)
}

void Party::loadSprites(std::string name){

    for(auto &t : textures){
        switch((t.first).find(name)){
            case std::string::npos:
                break;

            default:
                sprites.emplace(t.first, *getTexture(t.first));
                break;
        }
    }
}

sf::Sprite Party::getSprite(const std::string& name){
    auto found = sprites.find(name);
    if(found == sprites.end())
        throw std::runtime_error ("Party::getSprite(const std::string&) - Aucun sprite de ce nom " + name);

    return found->second;
}

void Party::loadRectangleShape(std::string name){
    for(auto &t : textures){
        switch((t.first).find(name)){
            case std::string::npos:
                break;

            default:
                sf::Vector2u vectu = (t.second)->getSize();
                sf::Vector2f vectf(vectu.x, vectu.y);
                rectangleShapes.emplace(t.first, new sf::RectangleShape(vectf));
                break;
        }
    }
}

sf::RectangleShape Party::getRectangleShape(const std::string& name){
    auto found = rectangleShapes.find(name);
    if(found == rectangleShapes.end())
        throw std::runtime_error ("Party::getRectangleShape(const std::string&) - Aucun rectangleShape de ce nom " + name);

    return *found->second;
}

void Party::loadAnimation(){

    walkingAspenUp.setSpriteSheet(*getTexture("AspenBack"));
    walkingAspenUp.addFrame(sf::IntRect(0, 0, 40, 80));
    walkingAspenUp.addFrame(sf::IntRect(40, 0, 40, 80));
    walkingAspenUp.addFrame(sf::IntRect(0, 0, 40, 80));
    walkingAspenUp.addFrame(sf::IntRect(80, 0, 40, 80));

    walkingAspenRight.setSpriteSheet(*getTexture("AspenRight"));
    walkingAspenRight.addFrame(sf::IntRect(0, 0, 40, 80));
    walkingAspenRight.addFrame(sf::IntRect(40, 0, 40, 80));
    walkingAspenRight.addFrame(sf::IntRect(0, 0, 40, 80));
    walkingAspenRight.addFrame(sf::IntRect(80, 0, 40, 80));

    walkingAspenDown.setSpriteSheet(*getTexture("AspenFront"));
    walkingAspenDown.addFrame(sf::IntRect(0, 0, 40, 80));
    walkingAspenDown.addFrame(sf::IntRect(40, 0, 40, 80));
    walkingAspenDown.addFrame(sf::IntRect(0, 0, 40, 80));
    walkingAspenDown.addFrame(sf::IntRect(80, 0, 40, 80));

    walkingAspenLeft.setSpriteSheet(*getTexture("AspenLeft"));
    walkingAspenLeft.addFrame(sf::IntRect(0, 0, 40, 80));
    walkingAspenLeft.addFrame(sf::IntRect(40, 0, 40, 80));
    walkingAspenLeft.addFrame(sf::IntRect(0, 0, 40, 80));
    walkingAspenLeft.addFrame(sf::IntRect(80, 0, 40, 80));

    currentAnimation = &walkingAspenDown;
    aspenAnimated.setFrameTime(sf::seconds(0.15f));
    aspenAnimated.setLooped(true);
    aspenAnimated.setPosition(posAspen.getPosition(true), posAspen.getPosition(false));
}

void Party::setFrameSprite(Room& curRoom){ // /!\ Peut être a modifier a cause des door[i]
    std::vector<Door*> door = curRoom.getDoors();
    sf::Sprite frame;

    unsigned size = sFrames.size();
    for (unsigned i = 0 ; i < size ; ++i)
        sFrames.pop_back();

    for(unsigned i = 0; i < door.size(); ++i){
        if(door[i]){
            switch(i){
                case 0:
                    frame = getSprite("FrameN");
                    frame.setPosition(arch.DoorN[0][0], arch.DoorN[0][1]);
                    break;

                case 1:
                    frame = getSprite("FrameE");
                    frame.setPosition(arch.DoorE[0][0], arch.DoorE[0][1]);
                    break;

                case 2:
                    frame = getSprite("FrameS");
                    frame.setPosition(arch.DoorS[0][0], arch.DoorS[0][1]);
                    break;

                case 3:
                    frame = getSprite("FrameW");
                    frame.setPosition(arch.DoorW[0][0], arch.DoorW[0][1]);
                    break;

                default:
                    break;
            }
            sFrames.push_back(frame);
        }
    }
}

void Party::setSpritesForCurrentRoom(){
    Room* curRoom = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false));
	
	if (curRoom)
	{
		sRoom = getSprite(curRoom->getStringType()); // on charge la map
		sRoom.setPosition(0.f, 0.f);

		    // On charge les différent éléments de la salle

		setFrameSprite(*curRoom);
	}
}

void Party::setWall(){

    for(unsigned i = 0; i < 8; ++i){
        sf::Vector2f vect(arch.Walls[i][2], arch.Walls[i][3]);
        sf::RectangleShape rect(vect); // set de la taille du rectangle
        rect.setPosition(arch.Walls[i][0], arch.Walls[i][1]); // on set la position du rectangle
        Walls.push_back(rect);
    }
    
    wallsCollider.pushBodies(Walls.begin(), Walls.end());
}

void Party::setHole(Room& curRoom){

    unsigned size = Holes.size();
    for(unsigned i = 0; i < size; ++i)
        Holes.pop_back();

    switch(curRoom.getType()){
        case roomType::Room2NS1:
            for(unsigned i = 0; i < 28; ++i){
                sf::RectangleShape hole({60.f, 60.f}); //set la size
                hole.setPosition(arch.Hole2NS1[i][0], arch.Hole2NS1[i][1]); // set la position
                Holes.push_back(hole);
            }
            break;

        case roomType::Room2WE1:
            for(unsigned i = 0; i < 19; ++i){
                sf::RectangleShape hole({60.f, 60.f}); //set la size
                hole.setPosition(arch.Hole2WE1[i][0], arch.Hole2WE1[i][1]); // set la position
                Holes.push_back(hole);
            }
            break;

        case roomType::Room1N:
            for(unsigned i = 0; i < 20; ++i){
                sf::RectangleShape hole({60.f, 60.f}); //set la size
                hole.setPosition(arch.Hole1N[i][0], arch.Hole1N[i][1]); // set la position
                Holes.push_back(hole);
            }
            break;

        case roomType::Room1S:
            for(unsigned i = 0; i < 22; ++i){
                sf::RectangleShape hole({60.f, 60.f}); //set la size
                hole.setPosition(arch.Hole1S[i][0], arch.Hole1S[i][1]); // set la position
                Holes.push_back(hole);
            }
            break;

        case roomType::Room1W:
            for(unsigned i = 0; i < 16; ++i){
                sf::RectangleShape hole({60.f, 60.f}); //set la size
                hole.setPosition(arch.Hole1W[i][0], arch.Hole1W[i][1]); // set la position
                Holes.push_back(hole);
            }
            break;

        case roomType::Room3NEW:
            for(unsigned i = 0; i < 10; ++i){
                sf::RectangleShape hole({60.f, 60.f}); //set la size
                hole.setPosition(arch.Hole3NEW[i][0], arch.Hole3NEW[i][1]); // set la position
                Holes.push_back(hole);
            }
            break;

        case roomType::Room3ESW:
            for(unsigned i = 0; i < 12; ++i){
                sf::RectangleShape hole({60.f, 60.f}); //set la size
                hole.setPosition(arch.Hole3ESW[i][0], arch.Hole3ESW[i][1]); // set la position
                Holes.push_back(hole);
            }
            break;

        default:
            break;
    }
    
    holesCollider.pushBodies(Holes.begin(), Holes.end());
}

void Party::setDoorOpenRectangleShape(Room& curRoom){
    std::vector<Door*> doors = curRoom.getDoors();
    sf::RectangleShape door;

    unsigned size = sDoors.size();
    for (unsigned i = 0 ; i < size ; ++i)
        sDoors.pop_back();

    for(unsigned i = 0; i < doors.size(); ++i){
        if(doors[i]){
            switch(i){
                case 0:
                    door = getRectangleShape("DoorOpenN");
                    door.setPosition(arch.DoorN[1][0], arch.DoorN[1][1]);
                    door.setTexture(getTexture("DoorOpenN"));
                    break;

                case 1:
                    door = getRectangleShape("DoorOpenE");
                    door.setPosition(arch.DoorE[1][0], arch.DoorE[1][1]);
                    door.setTexture(getTexture("DoorOpenE"));
                    break;

                case 2:
                    door = getRectangleShape("DoorOpenS");
                    door.setPosition(arch.DoorS[1][0], arch.DoorS[1][1]);
                    door.setTexture(getTexture("DoorOpenS"));
                    break;

                case 3:
                    door = getRectangleShape("DoorOpenW");
                    door.setPosition(arch.DoorW[1][0], arch.DoorW[1][1]);
                    door.setTexture(getTexture("DoorOpenW"));
                    break;

                default:
                    break;
            }
        }
        else{
            door.setFillColor(sf::Color(0, 0, 0, 0));
            switch(i){
                case 0:
                    door.setPosition(arch.DoorN[1][0], arch.DoorN[1][1]);
                    door.setSize({120.f, 80.f});
                    break;

                case 1:
                    door.setPosition(arch.DoorE[1][0], arch.DoorE[1][1]);
                    door.setSize({80.f, 1200.f});
                    break;

                case 2:
                    door.setPosition(arch.DoorS[1][0], arch.DoorS[1][1]);
                    door.setSize({120.f, 80.f});
                    break;

                case 3:
                    door.setPosition(arch.DoorW[1][0], arch.DoorW[1][1]);
                    door.setSize({80.f, 1200.f});
                    break;
            }
        }
        
        sDoors.push_back(door);
    }
    
    for (unsigned i = 0; i < doors.size(); ++i){
		if (doors[i]){
			doorsCollider.pushBody(sDoors[i]);
		}else{
			wallsCollider.pushBody(sDoors[i]);
		}
	}
}

void Party::setDoorCloseRectangleShape(Room& curRoom){
    std::vector<Door*> doors = curRoom.getDoors();
    sf::RectangleShape door;

    unsigned size = sDoors.size();
    for (unsigned i = 0 ; i < size ; ++i)
        sDoors.pop_back();

    for(unsigned i = 0; i < doors.size(); ++i){
        if(doors[i]){
            switch(i){
                case 0:
                    door = getRectangleShape("DoorCloseN");
                    door.setPosition(arch.DoorN[1][0], arch.DoorN[1][1]);
                    door.setTexture(getTexture("DoorCloseN"));
                    break;

                case 1:
                    door = getRectangleShape("DoorCloseE");
                    door.setPosition(arch.DoorE[1][0], arch.DoorE[1][1]);
                    door.setTexture(getTexture("DoorCloseE"));
                    break;

                case 2:
                    door = getRectangleShape("DoorCloseS");
                    door.setPosition(arch.DoorS[1][0], arch.DoorS[1][1]);
                    door.setTexture(getTexture("DoorCloseS"));
                    break;

                case 3:
                    door = getRectangleShape("DoorCloseW");
                    door.setPosition(arch.DoorW[1][0], arch.DoorW[1][1]);
                    door.setTexture(getTexture("DoorCloseW"));
                    break;

                default:
                    break;
            }
		}
        else{
            door.setFillColor(sf::Color(0, 0, 0, 0));
            switch(i){
                case 0:
                    door.setPosition(arch.DoorN[1][0], arch.DoorN[1][1]);
                    door.setSize({120.f, 80.f});
                    break;

                case 1:
                    door.setPosition(arch.DoorE[1][0], arch.DoorE[1][1]);
                    door.setSize({80.f, 1200.f});
                    break;

                case 2:
                    door.setPosition(arch.DoorS[1][0], arch.DoorS[1][1]);
                    door.setSize({120.f, 80.f});
                    break;

                case 3:
                    door.setPosition(arch.DoorW[1][0], arch.DoorW[1][1]);
                    door.setSize({80.f, 1200.f});
                    break;
            }
        }
        
        sDoors.push_back(door);
    }
    
    for (unsigned i = 0; i < doors.size(); ++i){
		if (doors[i]){
			doorsCollider.pushBody(sDoors[i]);
		}else{
			wallsCollider.pushBody(sDoors[i]);
		}
	}
}

void Party::setRockRectangleShape(Room& curRoom){
    std::vector<Rock> rocks = curRoom.getRocks();
    sf::RectangleShape rock;

    unsigned size = sRocks.size();
    for (unsigned i = 0 ; i < size ; ++i)
        sRocks.pop_back();

    if(! rocks.empty()) {
        for (unsigned k = 0; k < rocks.size(); ++k) {
            unsigned random = (rand()%30)%3+1;
            rock = getRectangleShape("Rock"+std::to_string(random));
            rock.setPosition(rocks[k].getPosition(true), rocks[k].getPosition(false));
            rock.setTexture(getTexture("Rock"+std::to_string(random)));

            sRocks.push_back(rock);
        }
    }
    
    rocksCollider.pushBodies(sRocks.begin(), sRocks.end());
}

//void Party::setMonsterRectangleShape(Room curRoom){std::vector<Entity*> monster = curRoom.getMonsters();}

void Party::setChestRectangleShape(Room& curRoom){  //sf::chest le mettre en vector
    Chest* chest = curRoom.getChest();

    sf::RectangleShape ches;
    unsigned size = sChest.size();
    for(unsigned i = 0; i < size; ++i)
        sChest.pop_back();

    if(chest){
        switch(curRoom.getType()){
            case roomType::Room3ESW:
                ches = getRectangleShape("ChestCloseN");
                ches.setPosition(arch.Chest3ESW[0], arch.Chest3ESW[1]);
                ches.setTexture(getTexture("ChestCloseN"));
                break;

            case roomType::Room1N:
                ches = getRectangleShape("ChestCloseN");
                ches.setPosition(arch.Chest1N[0], arch.Chest1N[1]);
                ches.setTexture(getTexture("ChestCloseN"));
                break;

            case roomType::Room1E:
                ches = getRectangleShape("ChestCloseW");
                ches.setPosition(arch.Chest1E[0], arch.Chest1E[1]);
                ches.setTexture(getTexture("ChestCloseW"));
                break;

            case roomType::Room1S:
                ches = getRectangleShape("ChestCloseN");
                ches.setPosition(arch.Chest1S[0], arch.Chest1S[1]);
                ches.setTexture(getTexture("ChestCloseN"));
                break;

            case roomType::Room1W:
                ches = getRectangleShape("ChestCloseE");
                ches.setPosition(arch.Chest1W[0], arch.Chest1W[1]);
                ches.setTexture(getTexture("ChestCloseE"));
                break;

            default:
                break;
        }
        sChest.push_back(ches);
    }
    
    chestsCollider.pushBodies(sChest.begin(), sChest.end());

}

void Party::setTrapRectangleShape(Room& curRoom){

    unsigned size = sTrap.size();
    for(unsigned i = 0; i < size; ++i)
        sTrap.pop_back();

    if(curRoom.getType() == roomType::Boss){
        sf::RectangleShape trap;
        trap = getRectangleShape("Trap");
        trap.setPosition(610.f, 300.f);
        trap.setTexture(getTexture("Trap"));
        sTrap.push_back(trap);
    }
    
    trapCollider.pushBodies(sTrap.begin(), sTrap.end());
}

void Party::setRectangleShapeForCurrentRoom(){

    Room* curRoom = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false));

    if (curRoom) {

        setWall();
        setHole(*curRoom);
        setDoorOpenRectangleShape(*curRoom);
        //setDoorCloseRectangleShape(*curRoom);
        setRockRectangleShape(*curRoom);
        setChestRectangleShape(*curRoom);
        setTrapRectangleShape(*curRoom);
    }
}

void Party::setInventoryStats(){

    textStats.resize(0);

    sf::Text txtStat;
    txtStat.setFont(statsFont);
    txtStat.setCharacterSize(10);
    txtStat.setFillColor(sf::Color::White);
    txtStat.setOutlineColor(sf::Color::Black);
    txtStat.setOutlineThickness(1.f);

    txtStat.setString("Max Life :   "+ std::to_string(Aspen.getMaxLife()));
    txtStat.setPosition(arch.statInventory[0][0], arch.statInventory[0][1]);
    textStats.push_back(txtStat);

    txtStat.setString("Attack :   "+ std::to_string(Aspen.getAttack()));
    txtStat.setPosition(arch.statInventory[0][0], arch.statInventory[0][1] + 25.f);
    textStats.push_back(txtStat);

    txtStat.setString("AttackSpeed :   "+ std::to_string(Aspen.getAttackSpeed()));
    txtStat.setPosition(arch.statInventory[0][0], arch.statInventory[0][1] + 50.f);
    textStats.push_back(txtStat);

    txtStat.setString("Defence :   "+ std::to_string(Aspen.getDefence()));
    txtStat.setPosition(arch.statInventory[1][0], arch.statInventory[1][1]);
    textStats.push_back(txtStat);

    txtStat.setString("Speed :   "+ std::to_string(Aspen.getSpeed()));
    txtStat.setPosition(arch.statInventory[1][0], arch.statInventory[1][1] + 25.f);
    textStats.push_back(txtStat);

    txtStat.setString("Money :   "+ std::to_string(Aspen.getMoney()));
    txtStat.setPosition(arch.statInventory[1][0], arch.statInventory[1][1] + 50.f);
    textStats.push_back(txtStat);
}

void Party::setInventoryItem(){

    viewAspen.setSize({60.f, 120.f});
    viewAspen.setPosition(arch.inventoryAspen[0], arch.inventoryAspen[1]);
    sf::Texture *textu = getTexture("AspenFront");
    textu->setSmooth(true);
    viewAspen.setTexture(textu);
    viewAspen.setTextureRect(sf::IntRect(0, 0, 40, 80));

    playerInventory.setSize({480.f, 280.f});
    playerInventory.setPosition(arch.playerInventory[0], arch.playerInventory[1]);
    playerInventory.setTexture(getTexture("PlayerInventory"));

    sf::RectangleShape item;
    
    sf::Text txt;
    txt.setFont(objectsFont);
    txt.setCharacterSize(10);
    txt.setFillColor(sf::Color::White);
    txt.setOutlineColor(sf::Color::Black);
    txt.setOutlineThickness(1.f);
    
    objectsNumber.clear();
    bagItem.clear();
	stuffItem.clear();

    for (unsigned i = 0; i < playerBagSize; ++i){
        const Object* object = Aspen.getInventoryObject(i);

        if(object){
            item.setSize({50.f, 50.f});
            item.setPosition(arch.itemBag[i][0], arch.itemBag[i][1]);
            item.setFillColor(sf::Color::Red);
            bagItem.emplace(i, item);
            
            if (object->getObjectNumber() > 1){
                txt.setString(std::to_string(object->getObjectNumber()));
                
                sf::FloatRect bounds = txt.getLocalBounds();
                txt.setOrigin({bounds.width, bounds.height});
                txt.setPosition(arch.itemBag[i][0] + 48.f, arch.itemBag[i][1] + 48.f);
                
                objectsNumber.emplace(i, txt);
            }
        }
        else{
            item.setSize({50.f, 50.f});
            item.setPosition(arch.itemBag[i][0], arch.itemBag[i][1]);
            item.setFillColor(sf::Color::Yellow);
            bagItem.emplace(i, item);
        }
    }

    for (unsigned i = 0; i < playerStuffSize; ++i){
        const Object* object = Aspen.getInventoryStuff(i);

        if(object){
            item.setSize({50.f, 50.f});
            item.setPosition(arch.itemStuff[i][0], arch.itemStuff[i][1]);
            item.setFillColor(sf::Color::Red);
            stuffItem.emplace(i, item);
            
            if (object->getObjectNumber() > 1){
                txt.setString(std::to_string(object->getObjectNumber()));
                
                sf::FloatRect bounds = txt.getLocalBounds();
                txt.setOrigin({bounds.width, bounds.height});
                txt.setPosition(arch.itemStuff[i][0] + 48.f, arch.itemStuff[i][1] + 48.f);
                
                objectsNumber.emplace(i, txt);
            }
        }
        else{
            item.setSize({50.f, 50.f});
            item.setPosition(arch.itemStuff[i][0], arch.itemStuff[i][1]);
            item.setFillColor(sf::Color::Yellow);
            stuffItem.emplace(i, item);
        }
    }
    
    sInventoryCursor.setSize({50.f, 50.f});

    sInventoryCursor.setFillColor(sf::Color::Transparent);
    sInventoryCursor.setOutlineThickness(2.f);
    sInventoryCursor.setOutlineColor(sf::Color::Blue);

        // player's stats
    setInventoryStats();
}

void Party::setChestItem(Room& curRoom){
    sf::RectangleShape item;
    Chest* chest = curRoom.getChest();

    chestInventory.setSize({480.f, 280.f});
    chestInventory.setPosition(arch.chestInventory[0], arch.chestInventory[1]);
    chestInventory.setTexture(getTexture("ChestInventory"));

    if(chest){
        chestItem.clear();
        std::cout << chestOpen << std::endl;

        for (unsigned i = 0; i < chestSize; ++i){
            const Object* object = chest->getItem(i);

            if(object){
                item.setSize({50.f, 50.f});
                item.setPosition(arch.itemChest[i][0], arch.itemChest[i][1]);
                item.setFillColor(sf::Color::Red);
                chestItem.emplace(i, item);
            }
            else{
                item.setSize({50.f, 50.f});
                item.setPosition(arch.itemChest[i][0], arch.itemChest[i][1]);
                item.setFillColor(sf::Color::Yellow);
                chestItem.emplace(i, item);
            }
        }
    }
}

void Party::setScrollingMenu(){
    
    rectangleShapeScrolling.resize(0);
    textScrolling.resize(0);
    
    scrollingValue = 1;
    scrollingIndex = 0;

    sf::RectangleShape scrollMenu;
    scrollMenu.setFillColor(sf::Color::White);
    scrollMenu.setOutlineColor(sf::Color::Red);
    scrollMenu.setOutlineThickness(2.f);

    sf::Text txt;
    txt.setFont(scroll);
    txt.setFillColor(sf::Color::Black);
    txt.setCharacterSize(12);
    
    sf::FloatRect bounds;
    
    scrollingMenuCursor.setFillColor(sf::Color::Transparent);
    scrollingMenuCursor.setOutlineColor(sf::Color::Blue);
    scrollingMenuCursor.setOutlineThickness(2.f);
    
    moveCursor.setSize({50.f, 50.f});
	moveCursor.setFillColor(sf::Color::Transparent);
	moveCursor.setOutlineColor(sf::Color::Green);
	moveCursor.setOutlineThickness(2.f);
    moveObjectIndex = inventoryIndex;

    switch(inventoryValue){ // RAJOUTER DANS 1/2 LA CONDITION DE SI LE COFFRE EST OUVERT, PROPOSER DE METTRE DANS LE COFFRE
        case 1: // unequip
            if(Aspen.getInventoryStuff(inventoryIndex)){
                txt.setString("Unequip");
                txt.setPosition(arch.itemStuff[inventoryIndex][0] + 52.f, arch.itemStuff[inventoryIndex][1]);
                textScrolling.push_back(txt);

                scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                bounds = txt.getGlobalBounds();
                scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                rectangleShapeScrolling.push_back(scrollMenu);
            }
            else{
                scrollingMenuOpen = false;
            }
            break;

        case 2: // deplacer, jeter, equip, (ajouter au coffre si le coffre est ouvert)
            if(Aspen.getInventoryObject(inventoryIndex)){
                if(Aspen.getInventoryObject(inventoryIndex)->getType() == Object::Type::monsterLoot){
                    scrollingValue = 2;
                    txt.setString("Move");
                    txt.setPosition(arch.itemBag[inventoryIndex][0] + 52.f, arch.itemBag[inventoryIndex][1]);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    txt.setString("Trash");
                    txt.setPosition(arch.itemBag[inventoryIndex][0] + 52.f, arch.itemBag[inventoryIndex][1] + 15.f);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);
                }
                else if(Aspen.getInventoryObject(inventoryIndex)->getType() == Object::Type::potion){
                    scrollingValue = 3;
                    txt.setString("Use");
                    txt.setPosition(arch.itemBag[inventoryIndex][0] + 52.f, arch.itemBag[inventoryIndex][1]);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    txt.setString("Move");
                    txt.setPosition(arch.itemBag[inventoryIndex][0] + 52.f, arch.itemBag[inventoryIndex][1] + 15.f);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    txt.setString("Trash");
                    txt.setPosition(arch.itemBag[inventoryIndex][0] + 52.f, arch.itemBag[inventoryIndex][1] + 30.f);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);
                }
                else{ // Si c'est un equipement
                    scrollingValue = 3;
                    txt.setString("Equip");
                    txt.setPosition(arch.itemBag[inventoryIndex][0] + 52.f, arch.itemBag[inventoryIndex][1]);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    txt.setString("Move");
                    txt.setPosition(arch.itemBag[inventoryIndex][0] + 52.f, arch.itemBag[inventoryIndex][1] + 15.f);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    txt.setString("Trash");
                    txt.setPosition(arch.itemBag[inventoryIndex][0] + 52.f, arch.itemBag[inventoryIndex][1] + 30.f);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);
                }
            }
            else{
                scrollingMenuOpen = false;
            }
            break;

        case 3: // ajouter a l'inventaire(enlever du coffre) seulement s'il y a un object, sinon fermer le scrollingMenu
            if(Aspen.getInventoryObject(inventoryIndex)){
                scrollingValue = 1;
                txt.setString("Add to inventory");
                txt.setPosition(arch.itemChest[inventoryIndex][0] + 52.f, arch.itemChest[inventoryIndex][1]);
                textScrolling.push_back(txt);

                scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                bounds = txt.getGlobalBounds();
                scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                rectangleShapeScrolling.push_back(scrollMenu);
            }
            else
                scrollingMenuOpen = false;
            break;

        default:
            break;
    }
}

void Party::updateScrollingMenu(){

    sf::Event event;
    while (mWindow.pollEvent(event)){
        if (event.type == sf::Event::KeyPressed) {

            switch(event.key.code){
                case sf::Keyboard::Space: // on reviens a l'inventaire
                    scrollingMenuOpen = false;
                    break;

                case sf::Keyboard::Z:// on monte dans la selection
                    if(scrollingIndex > 0)
                        scrollingIndex--;
                    break;

                case sf::Keyboard::S: // on descend dans la selections
                    if(scrollingIndex < scrollingValue - 1)
                        scrollingIndex++;
                    break;

                case sf::Keyboard::Return:// on appui sur entrer on applique le choix selectionné
					{
						std::string action = textScrolling[scrollingIndex].getString();

						if(action == std::string("Use")){// on utilise la potion donc on régénère la vie du player
							Aspen.usePotion(inventoryIndex);
                            setInventoryItem();
                            scrollingMenuOpen = false;
						}
						else if(action == std::string("Trash")){ // on jette l'item par terre
                            Aspen.removeInventoryObject(inventoryIndex);
                            setInventoryItem();
                            scrollingMenuOpen = false;
						}
						else if(action == std::string("Move")){ // on déplace l'objet là ou le player choisi l'emplacement via le cursor de playerInventory
                            moveObjectOpen = true;
						}
						else if(action == std::string("Equip")){ // On équip l'objet dans le stuff
                            Aspen.equipObject(inventoryIndex);
                            setInventoryItem();
                            scrollingMenuOpen = false;
						}
						else if(action == std::string("Unequip")) {
                            Aspen.unequipObject(inventoryIndex);
                            setInventoryItem();
                            scrollingMenuOpen = false;
						}
						else if(action == std::string("Add to inventory")){ // on ajoute l'objet du coffre a l'inventaire
							// TODO ajouter l'objet dans le sac du joueur
                            setInventoryItem();
                            setChestItem(*donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false)));
						    scrollingMenuOpen = false;
						}
					}
                    break;

                default:
                    break;
            }
        }
        else if (event.type == sf::Event::Closed){
            mWindow.close();
        }
    }
    
    sf::RectangleShape& pointedShape = rectangleShapeScrolling[scrollingIndex];
    scrollingMenuCursor.setPosition(pointedShape.getPosition());
    
    if (scrollingIndex + 1 < rectangleShapeScrolling.size()){
        sf::RectangleShape& nextToPointed = rectangleShapeScrolling[scrollingIndex + 1];
        scrollingMenuCursor.setSize({pointedShape.getSize().x, nextToPointed.getPosition().y - pointedShape.getPosition().y - 2.f});
    }
    else{
        scrollingMenuCursor.setSize(pointedShape.getSize());
    }
}

void Party::updateMoveObject(){
    sf::Event event;
	while (mWindow.pollEvent(event)){
		if (event.type == sf::Event::KeyPressed){
			switch(event.key.code){
				case sf::Keyboard::Z: // On monte dans l'inventaire
                    if (moveObjectIndex != 0)
                        --moveObjectIndex;
					break;

				case sf::Keyboard::Q: // On se décale a gauche
                    if(moveObjectIndex > 4){
                        moveObjectIndex -= 5;
                    }
					break;

				case sf::Keyboard::S: // on descend dans l'inventaire
                    if (moveObjectIndex != playerBagSize - 1)
                        ++moveObjectIndex;
					break;

				case sf::Keyboard::D: // on va a droite dans l'inventaire
                    if(moveObjectIndex < 5){
                        moveObjectIndex += 5;
                    }
                    break;

                case sf::Keyboard::Space: // on abandonne le move
                    moveObjectOpen = false;
                    break;
                
                case sf::Keyboard::Return: // on valide le mouvement
                    Aspen.swapObjects(inventoryIndex, moveObjectIndex);
                    setInventoryItem();
                    moveObjectOpen = false;
                    scrollingMenuOpen = false;
					inventoryIndex = moveObjectIndex;
                    break;
                    
                default: // On ne bouge pas le curseur
                    break;
            }
        }
        else if (event.type == sf::Event::Closed){
            mWindow.close();
        }
    }
    
    moveCursor.setPosition(arch.itemBag[moveObjectIndex][0], arch.itemBag[moveObjectIndex][1]);
}

void Party::updateInventory(){
	sf::Event event;
	while (mWindow.pollEvent(event)){
		if (event.type == sf::Event::KeyPressed){
			switch(event.key.code){
				case sf::Keyboard::Z: // On monte dans l'inventaire
					if (inventoryValue == 2){ // dans le sac
						if (inventoryIndex != 0)
							--inventoryIndex;
						else{
							inventoryValue = 1;
							inventoryIndex = playerStuffSize - 1;
						}
					}
					else if (inventoryValue == 1){ // dans le stuff
						if (inventoryIndex != 0)
							--inventoryIndex;
					}
					else if (inventoryValue == 3){ // dans le coffre
						if (inventoryIndex > 4){
							inventoryIndex -= 5;
						}
						else {
							inventoryValue = 2;
							inventoryIndex = playerBagSize - 1;
						}
					}
					break;

				case sf::Keyboard::Q: // On se décale a gauche
					if(inventoryValue == 2){
						if(inventoryIndex < 5){
							inventoryValue = 1;
							inventoryIndex = inventoryIndex < 3 ? inventoryIndex + 3 : playerStuffSize - 1;
						}
						else if(inventoryIndex > 4){
							inventoryIndex -= 5;
						}
					}
					else if(inventoryValue == 1){
						if(inventoryIndex > 2){
							inventoryIndex -= 3;
						}
					}
					else if (inventoryValue == 3){ // dans le coffre
						if (inventoryIndex != 0){
							--inventoryIndex;
						}
						else{
							inventoryValue = 2;
							inventoryIndex = playerBagSize - 1;
						}
					}
					break;

				case sf::Keyboard::S: // on descend dans l'inventaire
					if (inventoryValue == 2){ // dans le sac
						if (inventoryIndex != playerBagSize - 1)
							++inventoryIndex;
						else if (chestOpen){
							inventoryValue = 3;
							inventoryIndex = 0;
						}
					}
					else if (inventoryValue == 1){ // dans le stuff
						if (inventoryIndex != playerStuffSize - 1)
							++inventoryIndex;
						else{
							inventoryValue = 2;
							inventoryIndex = 0;
						}
					}
					else if (inventoryValue == 3){ // dans le coffre
						if (inventoryIndex < 15)
							inventoryIndex += 5;
					}
					break;

				case sf::Keyboard::D: // on va a droite dans l'inventaire
					if(inventoryValue == 2){
						if(inventoryIndex < 5){
							inventoryIndex += 5;
						}
						else if (chestOpen){
							inventoryValue = 3;
							inventoryIndex -= 5;
							if (inventoryIndex > 3)
								inventoryIndex = 3;
						}
					}
					else if(inventoryValue == 1){
						if(inventoryIndex > 2){
							inventoryValue = 2;
							inventoryIndex -= 3;
						}
						else if(inventoryIndex < 3){
							inventoryIndex += 3;
						}
					}
					else if (inventoryValue == 3){ // dans le coffre
						if (inventoryIndex < 19){
							++inventoryIndex;
						}
					}
					break;

				case sf::Keyboard::Space: // on ouvre les menu déroulant
					{
						scrollingMenuOpen = true;
						setScrollingMenu();
					}
					break;
				
				case sf::Keyboard::E: // on ferme l'inventaire
					inventoryOpen = false;
					chestOpen = false;
                    mIsMovingUp = false;
                    mIsMovingDown = false;
                    mIsMovingLeft = false;
                    mIsMovingRight = false;
					break;
					
				default: // On ne bouge pas le curseur
					break;
			}
		}
		else if (event.type == sf::Event::Closed){
			mWindow.close();
		}
    }
    
    switch(inventoryValue){
        case 1:
            sInventoryCursor.setPosition(arch.itemStuff[inventoryIndex][0], arch.itemStuff[inventoryIndex][1]);
            break;

        case 2:
            sInventoryCursor.setPosition(arch.itemBag[inventoryIndex][0], arch.itemBag[inventoryIndex][1]);
            break;

        case 3:
            sInventoryCursor.setPosition(arch.itemChest[inventoryIndex][0], arch.itemChest[inventoryIndex][1]);
            break;

        default:
            break;
    }

}

void Party::drawChestInventory(){
    Chest *chest = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getChest();

    if(chest && chestOpen){
        mWindow.draw(chestInventory);
		
        for(auto &c : chestItem)
            mWindow.draw(c.second);
		
		mWindow.draw(sInventoryCursor);
    }
}

void Party::drawPlayerInventory(){ // 1: stuff, 2: bag, 3: chest
    mWindow.draw(playerInventory);

    for(const auto &b : bagItem)
        mWindow.draw(b.second);

    for(const auto &s : stuffItem)
        mWindow.draw(s.second);
    
    for (const auto &t : objectsNumber)
        mWindow.draw(t.second);
    
    mWindow.draw(sInventoryCursor);
    
    if (scrollingMenuOpen){
        for (auto& rect : rectangleShapeScrolling){
            mWindow.draw(rect);
        }
        for (auto& text : textScrolling){
            mWindow.draw(text);
        }
        mWindow.draw(scrollingMenuCursor);
        
        if (moveObjectOpen){
            mWindow.draw(moveCursor);
        }
    }

    mWindow.draw(viewAspen);

    for(auto &txt : textStats)
        mWindow.draw(txt);
}

void Party::reloadRoom(){

	Room* curRoom = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false));
	loadSprites(curRoom->getStringType());
	
	trapCollider.clean();
	wallsCollider.clean();
	holesCollider.clean();
	rocksCollider.clean();
	doorsCollider.clean();
	// monstersCollider.clean();
	chestsCollider.clean();
	// projectilesCollider.clean();
	
	setSpritesForCurrentRoom();
    setRectangleShapeForCurrentRoom();
	
	setChestItem(*curRoom);
}

void Party::loadNextStage(){
    sTrap.pop_back();
    posAspen.setPosition(620.f, 310.f);
    posDonjon.setPosition(10, 10);
    donjon.nextStage();
    
    reloadRoom();
}

void Party::entityCollision(){

	sf::RectangleShape sPlayerCol ({(aspenAnimated.getLocalBounds()).width, (aspenAnimated.getLocalBounds()).height / 2.f});
	sPlayerCol.setOrigin({0.f, sPlayerCol.getSize().y});
	sPlayerCol.setPosition(aspenAnimated.getPosition().x, aspenAnimated.getPosition().y + (aspenAnimated.getLocalBounds()).height);
	sPlayerCol.move(0.f, (aspenAnimated.getLocalBounds()).height / 6.f);
	
	sf::Vector2f colDirection;
	sf::Vector2f posBegin = sPlayerCol.getPosition();
    
	Collider playerCol (sPlayerCol);
	
    playerCol.checkCollision(wallsCollider, colDirection, 0.f);

	if(playerCol.checkCollision(chestsCollider, colDirection, 0.f)){
	    inventoryOpen = true;
	    chestOpen = true;
		inventoryValue = 2;
        inventoryIndex = 0;
	}

	if (!Aspen.entityCanFly()){
		playerCol.checkCollision(holesCollider, colDirection, 0.f);
        playerCol.checkCollision(rocksCollider, colDirection, 0.f);
	}

	if (!sTrap.empty())
	{
		sf::RectangleShape& trap = sTrap[0];
        sf::RectangleShape sTrapCol ({trap.getSize().x, trap.getSize().y / 2.f});
        sTrapCol.setOrigin({0.f, sTrapCol.getSize().y});
        sTrapCol.setPosition(trap.getPosition().x, trap.getPosition().y + trap.getSize().y);

        Collider colt (sTrapCol);
        if(playerCol.checkCollision(colt, colDirection, 0.f)){
            loadNextStage();
		}
    }
	
	std::vector<Door*> door = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getDoors();
	if (playerCol.checkCollision(doorsCollider, colDirection, 0.f))
	{
		if (colDirection.y < 0.f && door[0] && door[0]->getOpen())
		{
			posDonjon.move(-1, 0);
			aspenAnimated.setPosition(arch.PlayerS[0], arch.PlayerS[1]);
			reloadRoom();
		}
		else if (colDirection.y > 0.f && door[2] && door[2]->getOpen())
		{
			posDonjon.move(1, 0);
			aspenAnimated.setPosition(arch.PlayerN[0], arch.PlayerN[1]);
			reloadRoom();
		}
		
		if (colDirection.x < 0.f && door[3] && door[3]->getOpen())
		{
			posDonjon.move(0, -1);
			aspenAnimated.setPosition(arch.PlayerE[0], arch.PlayerE[1]);
			reloadRoom();
		}
		else if (colDirection.x > 0.f && door[1] && door[1]->getOpen())
		{
			posDonjon.move(0, 1);
			aspenAnimated.setPosition(arch.PlayerW[0], arch.PlayerW[1]);
			reloadRoom();
		}
	}
	
	sf::Vector2f posEnd = sPlayerCol.getPosition();
		
	aspenAnimated.move(posEnd - posBegin);
}

void Party::processEvents(){
	
    sf::Event event;
    while (mWindow.pollEvent(event)){
        switch (event.type){
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;

            case sf::Event::Closed:
                mWindow.close();
                break;

            default:
                break;
        }
    }
}

void Party::handlePlayerInput(sf::Keyboard::Key key, bool isPressed){

    if (key == sf::Keyboard::Z)
        mIsMovingUp = isPressed;

    if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;

    if (key == sf::Keyboard::Q)
        mIsMovingLeft = isPressed;

    if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;

    if (isPressed && key == sf::Keyboard::E){
        inventoryOpen = true;
        inventoryValue = 2;
        inventoryIndex = 0;
    }
}

void Party::update(sf::Time deltaTime){

	sf::Vector2f movement(0.f, 0.f);

	if(mIsMovingUp){
		currentAnimation = &walkingAspenUp;
		movement.y -= PlayerSpeed;
		noKeyWasPressed = false;
	}

	if(mIsMovingDown){
		currentAnimation = &walkingAspenDown;
		movement.y += PlayerSpeed;
		noKeyWasPressed = false;
	}

	if(mIsMovingLeft){
		currentAnimation = &walkingAspenLeft;
		movement.x -= PlayerSpeed;
		noKeyWasPressed = false;
	}

	if(mIsMovingRight){
		currentAnimation = &walkingAspenRight;
		movement.x += PlayerSpeed;
		noKeyWasPressed = false;
	}

	aspenAnimated.play(*currentAnimation);
	aspenAnimated.move(movement * deltaTime.asSeconds());

	if (noKeyWasPressed)
	{
		aspenAnimated.stop();
	}
	noKeyWasPressed = true;

	aspenAnimated.update(deltaTime);

	entityCollision();
}

void Party::render(){

    mWindow.clear();
	
	mWindow.draw(sRoom);

	for(const auto &r : sRocks)
		mWindow.draw(r);

	for(const auto &f : sFrames)
		mWindow.draw(f);

	for(const auto &d : sDoors)
		mWindow.draw(d);

	for(const auto &c : sChest)
		mWindow.draw(c);

	for(const auto &t : sTrap)
		mWindow.draw(t);
	
	mWindow.draw(aspenAnimated);
	
	if(inventoryOpen) {
		drawPlayerInventory();
		if(chestOpen){
		    drawChestInventory();
		}
	}
		
    mWindow.display();
}
