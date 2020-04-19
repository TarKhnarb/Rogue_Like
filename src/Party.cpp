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

    loadRectangleShape("AspenF");
    sPlayer = getRectangleShape("AspenF");
    sPlayer.setPosition(posAspen.getPosition(true), posAspen.getPosition(false));
    sPlayer.setTexture(getTexture("AspenF"));
	
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
        processEvents();
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TimePerFrame){
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Party::loadTextures(){ // load dans le constructeur
        // Entity
            //Aspen
    sf::Texture* texture(new sf::Texture ());
    texture->loadFromFile("data/Textures/Entity/AspenB.png");
    textures.emplace("AspenB", std::move(texture));
	
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenB1.png");
    textures.emplace("AspenB1", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data//Textures/Entity/AspenB2.png");
    textures.emplace("AspenB2", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenF.png");
    textures.emplace("AspenF", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenF1.png");
    textures.emplace("AspenF1", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenF2.png");
    textures.emplace("AspenF2", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenL.png");
    textures.emplace("AspenL", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenL1.png");
    textures.emplace("AspenL1", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenL2.png");
    textures.emplace("AspenL2", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenL3.png");
    textures.emplace("AspenL3", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenR.png");
    textures.emplace("AspenR", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenR1.png");
    textures.emplace("AspenR1", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenR2.png");
    textures.emplace("AspenR2", std::move(texture));

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenR3.png");
    textures.emplace("AspenR3", std::move(texture));

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
    texture->loadFromFile("data/Textures/Door/trappe.png");
    textures.emplace("Trappe", std::move(texture));

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
}

sf::Texture* Party::getTexture(const std::string& nameText){ // récupere un etexture quand on en a besoin
    auto found = textures.find(nameText);
    if(found == textures.end())
        throw std::runtime_error ("Party::getTexture(const std::string&) - Aucune texture de ce nom " + nameText);

    return found->second; // ( si pas * on retourne un pointeur de texture)
}

// sf::Rect< T >::height/left/top/width

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
                hole.setOutlineColor(sf::Color::Red);
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
    }
}

void Party::reloadRoom()
{
	Room* curRoom = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false));
	loadSprites(curRoom->getStringType());
	
	setSpritesForCurrentRoom();
    setRectangleShapeForCurrentRoom();
}

void Party::entityCollision(){
	sf::RectangleShape sPlayerCol ({sPlayer.getSize().x, sPlayer.getSize().y / 2.f});
	sPlayerCol.setOrigin({0.f, sPlayerCol.getSize().y});
	sPlayerCol.setPosition(sPlayer.getPosition().x, sPlayer.getPosition().y + sPlayer.getSize().y);
	sPlayerCol.move(0.f, sPlayer.getSize().y / 6.f);
	
	sf::Vector2f posBegin = sPlayerCol.getPosition();
    for(auto &wall : Walls){
        Collision col = Collision(wall);
        (Collision(sPlayerCol)).checkCollision(col, 0.f);
    }

    for(auto &hole : Holes){
        Collision col = Collision(hole);
        (Collision(sPlayerCol)).checkCollision(col, 0.f);
    }
	
	std::vector<Door*> door = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getDoors();
	for (unsigned i = 0 ; i < sDoors.size() ; ++i){
		Collision col = Collision(sDoors[i]);
		if (Collision(sPlayerCol).checkCollision(col, 0.f) && door[i] && door[i]->getOpen())
		{
			switch (i)
			{
				case 0:
					posDonjon.move(-1, 0);
					sPlayer.setPosition(arch.PlayerS[0], arch.PlayerS[1]);
					reloadRoom();
					break;
				
				case 1:
					posDonjon.move(0, 1);
					sPlayer.setPosition(arch.PlayerW[0], arch.PlayerW[1]);
					reloadRoom();
					break;
				
				case 2:
					posDonjon.move(1, 0);
					sPlayer.setPosition(arch.PlayerN[0], arch.PlayerN[1]);
					reloadRoom();
					break;
				
				case 3:
					posDonjon.move(0, -1);
					sPlayer.setPosition(arch.PlayerE[0], arch.PlayerE[1]);
					reloadRoom();
					break;
				
				default:
					break;
			}
		}
	}
	sf::Vector2f posEnd = sPlayerCol.getPosition();
		
	sPlayer.move(posEnd - posBegin);
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

    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;

    else if (key == sf::Keyboard::Q)
        mIsMovingLeft = isPressed;

    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void Party::update(sf::Time deltaTime){
	
	sf::Vector2f movement(0.f, 0.f);
	
    if(mIsMovingUp)
		movement.y -= PlayerSpeed;
    if(mIsMovingDown)
		movement.y += PlayerSpeed;
    if(mIsMovingLeft)
		movement.x -= PlayerSpeed;
    if(mIsMovingRight)
		movement.x += PlayerSpeed;

    sPlayer.move(movement * deltaTime.asSeconds());
	
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
	
    mWindow.draw(sPlayer);
	
    mWindow.display();
}
