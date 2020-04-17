#include "Party.h"

Party::Party():
        posDonjon(10, 10),
        posAspen(620, 320),
        Aspen (posAspen.getPosition(true), posAspen.getPosition(false)),
        donjon(stageNumber, Aspen),
        mWindow(sf::VideoMode(1280, 720), "Aspen's Adventure"){


    loadTextures(); // On charge les textures

    loadSprites("Aspen"); // On charge les images de Aspen
    loadSprites("RoomStart"); // On charge la map de start
    loadSprites("Frame"); // on charge les encadrements de porte
    loadSprites("Door"); // On charge les portes ouvertes/fermées
    loadSprites("Rock");

    sPlayer = getSprite("AspenF");
    sPlayer.setPosition(320.f, 240.f);
}

Party::~Party(){
    for(auto &t : textures){
		if (t.second)
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
                sprites.emplace(t.first, getTexture(t.first));
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

void Party::setDoorOpenSprites(Room curRoom){ // /!\ Peut être a modifier a cause des door[i]
    std::vector<Door*> doors = curRoom.getDoors();
    sf::Sprite door;

    unsigned size = sDoors.size();
    for (unsigned i = 0 ; i < size ; ++i)
        sDoors.pop_back();

    for(unsigned i = 0; i < doors.size(); ++i){
        if(doors[i]){
            switch(i){
                case 0:
                    door = getSprite("DoorOpenN");
                    door.setPosition(arch.DoorN[1][0], arch.DoorN[1][1]);
                    break;

                case 1:
                    door = getSprite("DoorOpenE");
                    door.setPosition(arch.DoorE[1][0], arch.DoorE[1][1]);
                    break;

                case 2:
                    door = getSprite("DoorOpenS");
                    door.setPosition(arch.DoorS[1][0], arch.DoorS[1][1]);
                    break;

                case 3:
                    door = getSprite("DoorOpenW");
                    door.setPosition(arch.DoorW[1][0], arch.DoorW[1][1]);
                    break;

                default:
                    break;
            }
            sDoors.push_back(door);
        }
    }
}

void Party::setDoorCloseSprites(Room curRoom){ // /!\ Peut être a modifier a cause des door[i]
    std::vector<Door*> doors = curRoom.getDoors();
    sf::Sprite door;

    unsigned size = sDoors.size();
    for (unsigned i = 0 ; i < size ; ++i)
        sDoors.pop_back();

    for(unsigned i = 0; i < doors.size(); ++i){
        if(doors[i]){
            switch(i){
                case 0:
                    door = getSprite("DoorCloseN");
                    door.setPosition(arch.DoorN[1][0], arch.DoorN[1][1]);
                    break;

                case 1:
                    door = getSprite("DoorCloseE");
                    door.setPosition(arch.DoorE[1][0], arch.DoorE[1][1]);
                    break;

                case 2:
                    door = getSprite("DoorCloseS");
                    door.setPosition(arch.DoorS[1][0], arch.DoorS[1][1]);
                    break;

                case 3:
                    door = getSprite("DoorCloseW");
                    door.setPosition(arch.DoorW[1][0], arch.DoorW[1][1]);
                    break;

                default:
                    break;
            }
            sDoors.push_back(door);
        }
    }
}

void Party::setFrameSprites(Room curRoom){ // /!\ Peut être a modifier a cause des door[i]
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

void Party::setRockSprites(Room curRoom){
    std::vector<Rock> rocks = curRoom.getRocks();
    sf::Sprite rock;

    unsigned size = sRocks.size();
    for (unsigned i = 0 ; i < size ; ++i)
        sRocks.pop_back();

    if(! rocks.empty()) {
        for (unsigned k = 0; k < rocks.size(); ++k) {
            rock = getSprite("Rock"+std::to_string((rand()%30)%3+1));
            rock.setPosition(rocks[k].getPosition(true), rocks[k].getPosition(false));

            sRocks.push_back(rock);
        }
    }
}

//void Party::setMonsterSprites(Room curRoom){std::vector<Entity*> monster = curRoom.getMonsters();}

void Party::setChestSprites(Room curRoom){  //sf::chest le mettre en vector
    Chest* chest = curRoom.getChest();

    sf::Sprite ches;
    unsigned size = sChest.size();
    for(unsigned i = 0; i < size; ++i)
        sChest.pop_back();

    if(chest){
        switch(curRoom.getType()){
            case roomType::Room3ESW:
                ches = getSprite("ChestCloseN");
                ches.setPosition(arch.Chest3ESW[0], arch.Chest3ESW[1]);
                break;

            case roomType::Room1N:
                ches = getSprite("ChestCloseS");
                ches.setPosition(arch.Chest1N[0], arch.Chest1N[1]);
                break;

            case roomType::Room1E:
                ches = getSprite("ChestCloseW");
                ches.setPosition(arch.Chest1E[0], arch.Chest1E[1]);
                break;

            case roomType::Room1S:
                ches = getSprite("ChestCloseN");
                ches.setPosition(arch.Chest1S[0], arch.Chest1S[1]);
                break;

            case roomType::Room1W:
                ches = getSprite("ChestCloseE");
                ches.setPosition(arch.Chest1W[0], arch.Chest1W[1]);
                break;

            default:
                break;
        }
        sChest.push_back(ches);
    }

}

void Party::setSpritesForCurrentRoom(){
    Room curRoom = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false));

    sRoom = getSprite(curRoom.getStringType()); // on charge la map
    sRoom.setPosition(0.f, 0.f);

        // On charge les différent éléments de la salle
    setFrameSprites(curRoom);
    setDoorOpenSprites(curRoom);
    setRockSprites(curRoom);
    setChestSprites(curRoom);
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
		
		//if (!test.intersects(sRock.getGlobalBounds()))
			movement.y -= realSpeed;
	}
	
    if(mIsMovingDown)
	{
		test.height += realSpeed;
		
	//	if (!test.intersects(sRock.getGlobalBounds()))
			movement.y += realSpeed;
	}
	
    if(mIsMovingLeft)
	{
        test.left -= realSpeed;
		test.width += realSpeed;
		
		//if (!test.intersects(sRock.getGlobalBounds()))
			movement.x -= realSpeed;
	}
	
    if(mIsMovingRight)
	{
        test.width += realSpeed;
		
		//if (!test.intersects(sRock.getGlobalBounds()))
			movement.x += realSpeed;
	}

    sPlayer.move(movement);
}

void Party::render(){

    setSpritesForCurrentRoom();

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
