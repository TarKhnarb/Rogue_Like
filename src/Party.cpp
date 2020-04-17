#include "Party.h"
#include "Archetype.h"

Party::Party():
        posDonjon(10, 10),
        Aspen (620, 320),
        donjon(stageNumber, Aspen),
        mWindow(sf::VideoMode(640, 480), "Aspen's Adventure"){

    donjon.generate(); // On génere le premier etage du donjon
    loadTextures(); // On charge les textures

    loadSprites("Aspen"); // On charge les images de Aspen
    loadsprites("RoomStart"); // On charge la map de start
    loadsprites("Frame"); // on charge les encadrements de porte
    loadsprites("Door"); // On charge les portes ouvertes/fermées
    loadsprites("Rock");

    sPlayer = getSprite("sAspenF");
    sPlayer.setPosition(320.f, 240.f);
}

Party::~Party(){
    for(auto &t : textures){
        delete t.second;
        t.second = nullptr;
    }
}

void Party::run(){

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

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
    textures.emplace("AspenB", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenB1.png");
    textures.emplace("AspenB1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data//Textures/Entity/AspenB2.png");
    textures.emplace("AspenB2", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenF.png");
    textures.emplace("AspenF", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenF1.png");
    textures.emplace("AspenF1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenF2.png");
    textures.emplace("AspenF2", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenL.png");
    textures.emplace("AspenL", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenL1.png");
    textures.emplace("AspenL1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenL2.png");
    textures.emplace("AspenL2", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenL3.png");
    textures.emplace("AspenL3", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenR.png");
    textures.emplace("AspenR", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenR1.png");
    textures.emplace("AspenR1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenR2.png");
    textures.emplace("AspenR2", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Entity/AspenR3.png");
    textures.emplace("AspenR3", texture);

        // Room
            // Start/Boss
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Start.jpg");
    textures.emplace("RoomStart", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Boss.jpg");
    textures.emplace("RoomBoss", texture);

            // 1 Door
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room1E.jpg");
    textures.emplace("Room1E", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room1N.jpg");
    textures.emplace("Room1N", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room1S.jpg");
    textures.emplace("Room1S", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room1W.jpg");
    textures.emplace("Room1W", texture);

            // 2 Doors
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room2NS1.jpg");
    textures.emplace("Room2NS1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room2NS2.jpg");
    textures.emplace("Room2NS2", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room2WE1.jpg");
    textures.emplace("Room2WE1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room2WE2.jpg");
    textures.emplace("Room2WE2", texture);

            // 3 Doors
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room3ESW.jpg");
    textures.emplace("RoomESW", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room3NES.jpg");
    textures.emplace("Room3NES", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room3NEW.jpg");
    textures.emplace("Room3NEW", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room3NSW.jpg");
    textures.emplace("Room3NSW", texture);

            // 4 Doors
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room4NESW1.jpg");
    textures.emplace("Room4NESW1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Room/Room4NESW2.jpg");
    textures.emplace("Room4NESW2", texture);

        // Rocks
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Rock/Rock1.png");
    textures.emplace("Rock1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Rock/Rock2.png");
    textures.emplace("Rock2", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Rock/Rock3.png");
    textures.emplace("Rock3", texture);

        // Frame
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Frame/FrameE.png");
    textures.emplace("FrameE", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Frame/FrameN.png");
    textures.emplace("FrameN", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Frame/FrameS.png");
    textures.emplace("FrameS", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Frame/FrameW.png");
    textures.emplace("FrameW", texture);

        //  Door
            // Open
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Open/DoorOpenE.png");
    textures.emplace("DoorOpenE", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Open/DoorOpenN.png");
    textures.emplace("DoorOpenN", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Open/DoorOpenS.png");
    textures.emplace("DoorOpenS", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Open/DoorOpenW.png");
    textures.emplace("DoorOpenW", texture);

            // Close
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Close/DoorCloseE.png");
    textures.emplace("DoorCloseE", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Close/DoorCloseN.png");
    textures.emplace("DoorCloseN", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Close/DoorCloseS.png");
    textures.emplace("DoorCloseS", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Door/Close/DoorCloseW.png");
    textures.emplace("DoorCloseW", texture);

        // Chest
            // Close
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Close/ChestCloseE.png");
    textures.emplace("ChestCloseE", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Close/ChestCloseN.png");
    textures.emplace("ChestCloseN", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Close/ChestCloseS.png");
    textures.emplace("ChestCloseS", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Close/ChestCloseW.png");
    textures.emplace("ChestCloseW", texture);

        // Open
    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Open/ChestOpenE.png");
    textures.emplace("ChestOpenE", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Open/ChestOpenN.png");
    textures.emplace("ChestOpenN", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Open/ChestOpenS.png");
    textures.emplace("ChestOpenS", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Textures/Chest/Open/ChestOpenW.png");
    textures.emplace("ChestOpenW", texture);
}

sf::Texture& Party::getTexture(const std::string& nameText){ // récupere un etexture quand on en a besoin
    auto found = textures.find(nameText);
    if(found == textures.end())
        throw std::runtime_error ("Party::getTexture(const std::string&) - Aucune texture de ce nom " + nameText);

    return *found->second; // ( si pas * on retourne un pointeur de texture)
}

// sf::Rect< T >::height/left/top/width

void Party::loadSprites(std::string name){

    for(auto &t : textures){
        switch((t.first).find(name)){
            case std::string::npos:
                break;

            default:
                sprites.emplace("s" + t.first, getTexture(t.first));
                break;
        }
    }
}

sf::Sprite Party::getSprite(const std::string& name){
    auto found = sprites.find(name);
    if(found == sprites.end())
        throw std::runtime_error ("Party::getSprite(const std::string&) - Aucune texture de ce nom " + name);

    return found->second;
}

void Party::setDoorOpenSprites(Room curRoom){ // /!\ Peut être a modifier a cause des door[i]
    std::vector<Door*> door = curRoom.getDoors();

    for(unsigned i = 0; i < door.size(); ++i){
        if(door[i]){
            switch(i){
                case 0:
                    sDoors.push_back(getSprites("DoorOpenN"));
                    sDoors[i].setPosition(DoorN[1][0], DoorN[1][1]);
                    break;

                case 1:
                    sDoors.push_back(getSprites("DoorOpenE"));
                    sDoors[i].setPosition(DoorE[1][0], DoorE[1][1]);
                    break;

                case 2:
                    sDoors.push_back(getSprites("DoorOpenS"));
                    sDoors[i].setPosition(DoorS[1][0], DoorS[1][1]);
                    break;

                case 3:
                    sDoors.push_back(getSprites("DoorOpenW"));
                    sDoors[i].setPosition(DoorW[1][0], DoorW[1][1]);
                    break;

                default:
                    break;
            }
        }
        else
            sDoor.reverve(1);
    }
}

void Party::setDoorCloseSprites(Room curRoom){ // /!\ Peut être a modifier a cause des door[i]
    std::vector<Door*> door = curRoom.getDoors();

    for(unsigned i = 0; i < door.size(); ++i){
        if(door[i]){
            switch(i){
                case 0:
                    sDoors.push_back(getSprites("DoorCloseN"));
                    sDoors[i].setPosition(DoorN[1][0], DoorN[1][1]);
                    break;

                case 1:
                    sDoors.push_back(getSprites("DoorCloseE"));
                    sDoors[i].setPosition(DoorE[1][0], DoorE[1][1]);
                    break;

                case 2:
                    sDoors.push_back(getSprites("DoorCloseS"));
                    sDoors[i].setPosition(DoorS[1][0], DoorS[1][1]);
                    break;

                case 3:
                    sDoors.push_back(getSprites("DoorCloseW"));
                    sDoors[i].setPosition(DoorW[1][0], DoorW[1][1]);
                    break;

                default:
                    break;
            }
        }
        else
            sDoor.reverve(1);
    }
}

void Party::setFrameSprites(Room curRoom){ // /!\ Peut être a modifier a cause des door[i]
    std::vector<Door*> door = curRoom.getDoors();

    for(unsigned i = 0; i < door.size(); ++i){
        if(door[i]){
            switch(i){
                case 0:
                    sFrame.push_back(getSprites("FrameN"));
                    sFrame[i].setPosition(DoorN[0][0], DoorN[0][1]);
                    break;

                case 1:
                    sFrame.push_back(getSprites("FrameE"));
                    sFrame[i].setPosition(DoorE[0][0], DoorE[0][1]);
                    break;

                case 2:
                    sFrame.push_back(getSprites("FrameS"));
                    sFrame[i].setPosition(DoorS[0][0], DoorS[0][1]);
                    break;

                case 3:
                    sFrame.push_back(getSprites("FrameW"));
                    sFrame[i].setPosition(DoorW[0][0], DoorW[0][1]);
                    break;

                default:
                    break;
            }
        }
        else
            sDoor.reverve(1);
    }
}

void Party::setRockSprites(Room curRoom){
    std::vector<Rock> rocks = curRoom.getRocks();

    if(rocks.size() > 0) {
        for (unsigned k = 0; k < rocks.size(); ++k) {

            sRocks.push_back(getSprite("Rock"+std::to_string((rand%30)%3+1))); // Permet de charher le sprite d'un des 3 rochers
            sRocks.setPosition(rocks[k].getPosition(true), rocks[k].getPosition(false));
        }
    }
}

//void Party::setMonsterSprites(Room curRoom){std::vector<Entity*> monster = curRoom.getMonsters();}

void Party::setChestCloseSprites(Room curRoom){
    Chest* chest = curRoom.getChest();
    if(chest){
        switch(curRoom.getType()){
            case roomType::Room3ESW:
                sf::Chest = getSprite("ChestCloseN");
                sf::Chest.setPosition(Chest3ESW[0], Chest3ESW[1]);
                break;

            case roomType::Room1N:
                sf::Chest = getSprite("ChestCloseS");
                sf::Chest.setPosition(Chest1N[0], Chest1N[1]);
                break;

            case roomType::Room1E:
                sf::Chest = getSprite("ChestCloseW");
                sf::Chest.setPosition(Chest1E[0], Chest1E[1]);
                break;

            case roomType::Room1S:
                sf::Chest = getSprite("ChestCloseN");
                sf::Chest.setPosition(Chest1S[0], Chest1S[1]);
                break;

            case roomType::Room1W:
                sf::Chest = getSprite("ChestCloseE");
                sf::Chest.setPosition(Chest1W[0], Chest1W[1]);
                break;

            default:
                break;
        }
    }

}

void Party::setSpritesForCurrentRoom(unsigned i, unsigned j){
    Room curRoom = donjon.getRoom(i, j);

    sRoom = getSprite(std::to_string(curRoom.getType())); // on charge la map


    switch (curRoom.getType()){

        case roomType::Start:

            break;

        case roomType::Boss:
            stream << "Z";
            break;

        case roomType::CommonStart:
            stream << "s";
            break;

        case roomType::Room2WE1 :
            stream << "A";
            break;

        case roomType::Room2WE2 :
            stream << "B";
            break;

        case roomType::Room2NS1 :
            stream << "C";
            break;

        case roomType::Room2NS2 :
            stream << "D";
            break;

        case roomType::Room4NESW1:
            stream << "E";
            break;

        case roomType::Room4NESW2:
            stream << "F";
            break;

        case roomType::Room1N:
            stream << "G";
            break;

        case roomType::Room1E:
            stream << "H";
            break;

        case roomType::Room1S:
            stream << "I";
            break;

        case roomType::Room1W :
            stream << "J";
            break;

        case roomType::Room3NEW:
            stream << "K";
            break;

        case roomType::Room3NSW:
            stream << "L";
            break;

        case roomType::Room3ESW:
            stream << "M";
            break;

        case roomType::Room3NES:
            stream << "N";
            break;

        default:
            break;
    }

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

	float realSpeed = PlayerSpeed * deltaTime.asSeconds();
	
    sf::FloatRect test = sPlayer.getGlobalBounds();
    test.height /= 3;
    test.top += test.height * 2;
	
	sf::Vector2f movement(0.f, 0.f);
	
    if(mIsMovingUp)
	{
        test.top -= realSpeed;
		test.height += realSpeed;
		
		if (!test.intersects(sRock.getGlobalBounds()))
			movement.y -= realSpeed;
	}
	
    if(mIsMovingDown)
	{
		test.height += realSpeed;
		
		if (!test.intersects(sRock.getGlobalBounds()))
			movement.y += realSpeed;
	}
	
    if(mIsMovingLeft)
	{
        test.left -= realSpeed;
		test.width += realSpeed;
		
		if (!test.intersects(sRock.getGlobalBounds()))
			movement.x -= realSpeed;
	}
	
    if(mIsMovingRight)
	{
        test.width += realSpeed;
		
		if (!test.intersects(sRock.getGlobalBounds()))
			movement.x += realSpeed;
	}

    sPlayer.move(movement);
}

void Party::render(){

    mWindow.clear();



    mWindow.draw(sPlayer);
    mWindow.display();
}
