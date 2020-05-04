#include "Party.h"

Party::Party():
        posDonjon(10, 10),
        posAspen(620, 310),
        Aspen (posAspen.getPosition(true), posAspen.getPosition(false)),
        donjon(stageNumber, &Aspen),
        mWindow(sf::VideoMode(1280, 720), "Aspen's Adventure"){


    elapsedTime = sf::Time::Zero;
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
    loadRectangleShape("RockBreak");

    loadRectangleShape("DoorOpenN");
    loadRectangleShape("DoorOpenE");
    loadRectangleShape("DoorOpenS");
    loadRectangleShape("DoorOpenW");

    loadRectangleShape("DoorCloseN");
    loadRectangleShape("DoorCloseE");
    loadRectangleShape("DoorCloseS");
    loadRectangleShape("DoorCloseW");

    loadRectangleShape("Trap");

    if (scroll.loadFromFile("data/Font/verdana.ttf")){ // charge le police d'écriture verdana
        objectsFont.loadFromFile("data/Font/verdana.ttf");
        statsFont.loadFromFile("data/Font/verdana.ttf");
    }
    else{
        throw std::runtime_error ("Failed to load data/Font/verdana.ttf");
    }

    loadAnimation();
    
    Aspen.addInventoryObject(16); // monsterLoot
	Aspen.addInventoryObject(47, 1); // potion
	Aspen.addInventoryObject(22); // helmet
    Aspen.addInventoryObject(25); // boots
    Aspen.addInventoryObject(37); // Projectile
    Aspen.addInventoryObject(43); // Projectile
    Aspen.addInventoryObject(34); // Projectile

    
	rocksCollider.setStyle(Style::Separated);
    flyingMonstersCollider.setStyle(Style::Separated);
    walkingMonstersCollider.setStyle(Style::Separated);

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
    
    for(auto p = sProjectiles.begin(); p != sProjectiles.end();){
        if(p->first)
            delete p->first;
        p = sProjectiles.erase(p);
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

            if(!inventoryOpen && !exceptionState){ // game state
                processEvents();
                update(TimePerFrame);
                
                if (inventoryOpen) // late update
                    updateInventory();
                
                if (exceptionState) // late update too
                    updateException();
            }
            else if (exceptionState){ // exception state
                updateException();
            }
            else if (!scrollingMenuOpen){ // inventory state
                try{
                    updateInventory();
                    
                    if (scrollingMenuOpen) // late update
                        updateScrollingMenu();
                }
                catch (std::logic_error& err){
                    exceptionText = std::string(err.what());
                    exceptionState = true;
                }
			}
			else if (!moveObjectOpen){ // srolling menu state
                updateScrollingMenu();
                
                if (moveObjectOpen) // late update
                    updateMoveObject();
            }
            else{ // move object state
                try{
                    updateMoveObject();
                }
                catch (std::logic_error& err){
                    exceptionText = std::string(err.what());
                    exceptionState = true;
                }
            }
            updateLife();
        }

        render();
    }
}

std::string Party::returnCsvItem(std::istringstream & ss){
    std::string res;
    std::getline(ss,res,',');
    return res;
}

void Party::loadTextures(){ // load dans le constructeur
    std::ifstream file;
    std::string filename = "data/Textures.csv";
    file.open(filename);

    if (file.is_open()) {
        std::string csvItem;
        std::string path, name;

        while (std::getline(file, csvItem)){

            std::istringstream iss(csvItem);

            path = returnCsvItem(iss);
            name = returnCsvItem(iss);

            sf::Texture *texture(new sf::Texture());
            texture->loadFromFile(path.c_str());
            textures.emplace(name.c_str(), std::move(texture));
        }
    }
    else
        throw std::runtime_error ("Failed to load " + filename);

    file.close();
}

sf::Texture* Party::getTexture(const std::string& nameText){ // récupere un etexture quand on en a besoin
    auto found = textures.find(nameText);
    if(found == textures.end())
        throw std::runtime_error ("Aucune texture de ce nom " + nameText);

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
        throw std::runtime_error ("Aucun sprite de ce nom " + name);

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
        throw std::runtime_error ("Aucun rectangleShape de ce nom " + name);

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

void Party::setRockChoice(Room& curRoom){
    std::vector<Rock> rocks = curRoom.getRocks();
    
    rocksChoice.resize(0);
    
    for (unsigned k = 0; k < rocks.size(); ++k) {
        rocksChoice.push_back((rand()%30)%3+1);
    }
}

void Party::setRockRectangleShape(Room& curRoom){
    std::vector<Rock> rocks = curRoom.getRocks();
    sf::RectangleShape rock;

    unsigned size = sRocks.size();
    for (unsigned i = 0 ; i < size ; ++i)
        sRocks.pop_back();
    
    size = sNoRocks.size();
    for (unsigned i = 0 ; i < size ; ++i)
        sNoRocks.pop_back();
    
    for (unsigned k = 0; k < rocks.size(); ++k) {
        if(rocks[k].getState()){
            unsigned random = rocksChoice[k];
            rock = getRectangleShape("Rock"+std::to_string(random));
            rock.setPosition(rocks[k].getPosition(true), rocks[k].getPosition(false));
            rock.setTexture(getTexture("Rock"+std::to_string(random)));
            
            sRocks.push_back(rock);
        }
        else{
            rock = getRectangleShape("RockBreak");
            rock.setPosition(rocks[k].getPosition(true), rocks[k].getPosition(false));
            rock.setTexture(getTexture("RockBreak"));
            
            sNoRocks.push_back(rock);
            
            sf::RectangleShape noRock;
            sRocks.push_back(noRock);
        }
    }
    
    rocksCollider.clean();
    rocksCollider.pushBodies(sRocks.begin(), sRocks.end());
}

void Party::setMonsterRectangleShape(Room& curRoom){
    std::vector<Entity*>& monster = curRoom.getMonsters();
    
    bool handleTime = actionTimeMonster.empty();

    sf::RectangleShape monst({80.f, 80.f});

    flyMonst.clear();

    walkMonst.clear();

    unsigned sizeF = sFlyingMonsters.size();
    for (unsigned i = 0; i < sizeF; ++i)
        sFlyingMonsters.pop_back();

    unsigned sizeW = sWalkingMonsters.size();
    for (unsigned i = 0; i < sizeW; ++i)
        sWalkingMonsters.pop_back();

    flyingMonstersCollider.clean();
    walkingMonstersCollider.clean();

    for(unsigned i = 0; i < monster.size(); ++i){
        if(monster[i]){

            monst.setTexture(getTexture(monster[i]->getName()));
            monst.setPosition(monster[i]->getPosition(true) - 40.f, monster[i]->getPosition(false) - 40.f);

            if(monster[i]->entityCanFly()){
                sFlyingMonsters.push_back(monst);
                flyMonst.push_back(monster[i]);
            }
            else{
                sWalkingMonsters.push_back(monst);
                walkMonst.push_back(monster[i]);
            }

            if(monster[i]->getName() == "VIH"){
                float angle;
                angle = (rand() % 360) * (4.f * atan(1.f) / 180.f);
                vectorVIH = sf::Vector2f(cos(angle) * 1.f, sin(angle) * 1.f);
            }

            if(handleTime){
                destinationMonster.push_back(sf::Vector2f ());
                actionTimeMonster.push_back(sf::Time::Zero);
                pauseTimeMonster.push_back(sf::Time::Zero);
                inActionMonster.push_back(false);
            }
        }
    }

    flyingMonstersCollider.pushBodies(sFlyingMonsters.begin(), sFlyingMonsters.end());
    walkingMonstersCollider.pushBodies(sWalkingMonsters.begin(), sWalkingMonsters.end());

}

void Party::setLootOnTheFloor(Entity& entity){
    unsigned  id = 0;
    unsigned random = rand()%4; // 0, 1, 2, 3
    if(random == 0){
        id = 58;
    }
    else if(random == 1){
        //Loot l'object caractéristique
        switch(entity.getEntityId()){
                // Monsters
            case 2: // Grippe-Espagnole
                // Loot ADN id: 60
                // Cellules id: 51
                if(rand()%2 == 0)
                    id = 60;
                else
                    id = 51;
                break;

            case 3: // Peste-Noire
                // loot sang infecté id: 57
                // loot Ribosomes id: 61
                if(rand()%2 == 0)
                    id = 57;
                else
                    id = 61;
                break;

            case 4: // Tenia
                // Hydroxyde de sodium id: 64
                // Membrane plasmique id: 54
                if(rand()%2 == 0)
                    id = 64;
                else
                    id = 54;
                break;

            case 5: // Listeria
                // Cytoplasme id: 59
                // Acide nucléique id: 50
                if(rand()%2 == 0)
                    id = 60;
                else
                    id = 51;
                break;
            case 6: // Blob
                // Spores id: 62
                // Cellulose id: 63
                if(rand()%2 == 0)
                    id = 62;
                else
                    id = 63;
                break;

                // Boss
            case 7: // Cymothoa-exigua
                // Noyau id: 53
                id = 53;
                break;

            case 8: // H1N1
                // Toxine botulique id: 56
                id = 56;
                break;

            case 9: // VIH
                // Cyanure id: 55
                id = 55;
                break;

            case 10: // COVID-19
                // Novichok id: 52
                id = 52;
                break;

            default:
                break;
        }
    }

    if(id != 0){
        sLoot.push_back(id);

        sf::Sprite item(*getTexture(std::to_string(id)));
        item.setPosition(entity.getPosition(true) - 10.f, entity.getPosition(false) - 10.f);
        item.scale(20.f/64.f, 20.f/64.f);

        sf::RectangleShape hitbox({20.f, 20.f});
        hitbox.setPosition(entity.getPosition(true) - 10.f, entity.getPosition(false) - 10.f);

        hitBoxLoots.push_back(hitbox);
        Loots.push_back(item);
    }

    lootCollider.clean();
    lootCollider.pushBodies(hitBoxLoots.begin(), hitBoxLoots.end());
}

void Party::drawLootOnTheFloor(){
    for(auto &l : Loots)
        mWindow.draw(l);
}

void Party::setLifeRectangleShape(){
    //sf::RectangleShape sMaxLife;
    //sf::RectangleShape sLife;


    sMaxLife.setSize({102.f, 22.f});
    sMaxLife.setPosition(9.f, 9.f);
    sMaxLife.setFillColor(sf::Color::Transparent);
    sMaxLife.setOutlineColor(sf::Color::White);
    sMaxLife.setOutlineThickness(4.f);

    sLife.setSize({100.f * (1.f - (Aspen.getMaxLife()-Aspen.getLife())/Aspen.getMaxLife()), 20.f});
    sLife.setPosition(10.f, 10.f);
    sLife.setFillColor(sf::Color::Green);
}

void Party::updateLife(){
    sLife.setSize({100.f * (1.f - (float)(Aspen.getMaxLife()-Aspen.getLife())/(float)Aspen.getMaxLife()), 20.f});
}

void Party::setAStar(Room& room){
    for (unsigned i = 0; i < 40; ++i){
        for (unsigned j = 0; j < 20; ++j){
            grid[j][i] = 0;
        }
    }
    
    unsigned x;
    unsigned y;
    
    std::vector<Rock>& rocks = room.getRocks();
    for (const auto& rock : rocks){
        if (!rock.getState())
            continue;
        
        x = (rock.getPosition(true) - 240) / 20;
        y = (rock.getPosition(false) - 160) / 20;
        
        // rocks are 40 * 40 px
        for (unsigned i = 0; i <= 1; ++i){
            for (unsigned j = 0; j <= 1; ++j){
                grid[y + j][x + i] = 1;
            }
        }
    }
    
    roomType type = room.getType();
    // On ne net pas les coffre pour eviter de bloquer les monstres
    switch (type){

        case Room2NS1:
            for (unsigned k = 0; k < 28; ++k){
                x = int(arch.Hole2NS1[k][0] - 240) / 20;
                y = int(arch.Hole2NS1[k][1] - 160) / 20;
                
                // holes are 60 * 60 px
                for (unsigned i = 0; i <= 2; ++i){
                    for (unsigned j = 0; j <= 2; ++j){
                        grid[y + j][x + i] = 1;
                    }
                }
            }
            break;
        
        case Room2WE1:
            for (unsigned k = 0; k < 19; ++k){
                x = int(arch.Hole2WE1[k][0] - 240) / 20;
                y = int(arch.Hole2WE1[k][1] - 160) / 20;
                
                // holes are 60 * 60 px
                for (unsigned i = 0; i <= 2; ++i){
                    for (unsigned j = 0; j <= 2; ++j){
                        grid[y + j][x + i] = 1;
                    }
                }
            }
            break;
            
        case Room1N:
            for (unsigned k = 0; k < 20; ++k){
                x = int(arch.Hole1N[k][0] - 240) / 20;
                y = int(arch.Hole1N[k][1] - 160) / 20;
                
                // holes are 60 * 60 px
                for (unsigned i = 0; i <= 2; ++i){
                    for (unsigned j = 0; j <= 2; ++j){
                        grid[y + j][x + i] = 1;
                    }
                }
            }
            break;
        
        case Room1S:
            for (unsigned k = 0; k < 22; ++k){
                x = int(arch.Hole1S[k][0] - 240) / 20;
                y = int(arch.Hole1S[k][1] - 160) / 20;
                
                // holes are 60 * 60 px
                for (unsigned i = 0; i <= 2; ++i){
                    for (unsigned j = 0; j <= 2; ++j){
                        grid[y + j][x + i] = 1;
                    }
                }
            }
            break;
            
        case Room1W:
            for (unsigned k = 0; k < 16; ++k){
                x = int(arch.Hole1W[k][0] - 240) / 20;
                y = int(arch.Hole1W[k][1] - 160) / 20;
                
                // holes are 60 * 60 px
                for (unsigned i = 0; i <= 2; ++i){
                    for (unsigned j = 0; j <= 2; ++j){
                        grid[y + j][x + i] = 1;
                    }
                }
            }
            break;
        
        case Room3ESW:
            for (unsigned k = 0; k < 12; ++k){
                x = int(arch.Hole3ESW[k][0] - 240) / 20;
                y = int(arch.Hole3ESW[k][1] - 160) / 20;
                
                // holes are 60 * 60 px
                for (unsigned i = 0; i <= 2; ++i){
                    for (unsigned j = 0; j <= 2; ++j){
                        grid[y + j][x + i] = 1;
                    }
                }
            }
            break;
        
        case Room3NEW:
            for (unsigned k = 0; k < 10; ++k){
                x = int(arch.Hole3NEW[k][0] - 240) / 20;
                y = int(arch.Hole3NEW[k][1] - 160) / 20;
                
                // holes are 60 * 60 px
                for (unsigned i = 0; i <= 2; ++i){
                    for (unsigned j = 0; j <= 2; ++j){
                        grid[y + j][x + i] = 1;
                    }
                }
            }
            break;
        
        default:
            break;
    }
}

void Party::updateGrippeEspagnole(Entity &entity, sf::Time deltaTime, unsigned index){
    float deltaX = destinationMonster[index].x - entity.getPosition(true);
    float deltaY = destinationMonster[index].y - entity.getPosition(false);
    
    if (deltaX * deltaX + deltaY * deltaY <= 100.f){
        return;
    }

    float angle = atan2(deltaY, deltaX);
    float realDeltaX = cos(angle) * entity.getSpeed() * 100.f * deltaTime.asSeconds();
    float realDeltaY = sin(angle) * entity.getSpeed() * 100.f * deltaTime.asSeconds();
    
    entity.moveEntity(realDeltaX, realDeltaY);
}

void Party::updatePesteNoire(Entity &entity, sf::Time deltaTime, unsigned index){
    float deltaX = destinationMonster[index].x - entity.getPosition(true);
    float deltaY = destinationMonster[index].y - entity.getPosition(false);

    float realDeltaX = entity.getSpeed() * 50.f * deltaTime.asSeconds();
    float realDeltaY = entity.getSpeed() * 50.f * deltaTime.asSeconds();

    if(abs(deltaX) < abs(deltaY)){

        if(deltaX > -20.f && deltaX < 20.f){
            // on tire
            if(deltaY < 0.f)
                setProjectileRectangleShape(entity, 0); // shoot en haut
            else
                setProjectileRectangleShape(entity, 2); //shoot en bas
        }
        else{
            //on se déplace suivant le signe de deltaX
            if(deltaX < 0.f)
                entity.moveEntity(-realDeltaX, 0);
            else
                entity.moveEntity(realDeltaX, 0);
        }
    }
    else{
        if(deltaY > -40.f && deltaY < 40.f){
            // on tire
            if(deltaX < 0.f)
                setProjectileRectangleShape(entity, 3); // shoot a gauche
            else
                setProjectileRectangleShape(entity, 1); // shoot a droite
        }
        else{
            //on se déplace suivant le signe de deltaY
            if(deltaY < 0.f)
                entity.moveEntity(0, -realDeltaY);
            else
                entity.moveEntity(0, realDeltaY);
        }
    }
}

void Party::updateTenia(Entity &entity, sf::Time deltaTime){
    Pair src = std::make_pair((int)((entity.getPosition(false) - 160.f)/20.f), (int)((entity.getPosition(true) - 240.f)/20.f));
    Pair dest = std::make_pair((int)((posAspen.getPosition(false) - 120.f)/20.f), (int)((posAspen.getPosition(true) - 220.f)/20.f));

    aStarSearch(grid, src, dest);

    float x = pathY() - (float)src.second;
    float y = pathX() - (float)src.first;

    sf::Vector2f movement (x, y);
    movement *= entity.getSpeed() * deltaTime.asSeconds();

    entity.moveEntity(movement.x, movement.y);
}

void Party::updateListeria(Entity &entity, sf::Time deltaTime){
    float deltaX = posAspen.getPosition(true) - entity.getPosition(true);
    float deltaY = posAspen.getPosition(false) - entity.getPosition(false);

    Pair src = std::make_pair((int)((entity.getPosition(false) - 160.f)/20.f), (int)((entity.getPosition(true) - 240.f)/20.f));
    Pair dest;

    if(abs(deltaX) < abs(deltaY))
        dest = std::make_pair((int)((entity.getPosition(false) - 160.f)/20.f), (int)((posAspen.getPosition(true) - 220.f)/20.f));
    else
        dest = std::make_pair((int)((posAspen.getPosition(false) - 120.f)/20.f), (int)((entity.getPosition(true) - 240.f)/20.f));

    aStarSearch(grid, src, dest);

    float y = pathX() - (float)src.first;
    float x = pathY() - (float)src.second;

    sf::Vector2f movement (x, y);
    movement *= entity.getSpeed() * deltaTime.asSeconds();

    entity.moveEntity(movement.x, movement.y);

    if(deltaX > -2.f && deltaX < 2.f){
        if(deltaY < 0.f)
            setProjectileRectangleShape(entity, 0);
        else
            setProjectileRectangleShape(entity, 2);
    }
    else if(deltaY > -4.f && deltaY < 4.f){
        if(deltaX < 0.f)
            setProjectileRectangleShape(entity, 3);
        else
            setProjectileRectangleShape(entity, 1);
    }

}

void Party::updateBlob(Entity &entity, sf::Time deltaTime){
    Pair src = std::make_pair((int)((entity.getPosition(false) - 160.f)/20.f), (int)((entity.getPosition(true) - 240.f)/20.f));
    Pair dest = std::make_pair((int)((posAspen.getPosition(false) - 120.f)/20.f), (int)((posAspen.getPosition(true) - 220.f)/20.f));

    aStarSearch(grid, src, dest, 10);

    float x = pathY() - (float)src.second;
    float y = pathX() - (float)src.first;

    sf::Vector2f movement (x, y);
    movement *= entity.getSpeed() * deltaTime.asSeconds();

    entity.moveEntity(movement.x, movement.y);
}

void Party::updateCymothoaExigua(Entity &entity, sf::Time deltaTime, unsigned index){
    float deltaX = destinationMonster[index].x - entity.getPosition(true);
    float deltaY = destinationMonster[index].y - entity.getPosition(false);

    if (deltaX * deltaX + deltaY * deltaY <= 100.f){
        return;
    }

    float angle = atan2(deltaY, deltaX);
    float realDeltaX = cos(angle) * entity.getSpeed() * 100.f * deltaTime.asSeconds();
    float realDeltaY = sin(angle) * entity.getSpeed() * 100.f * deltaTime.asSeconds();

    entity.moveEntity(realDeltaX, realDeltaY);
}

void Party::updateH1N1(Entity &entity, sf::Time deltaTime){
    Pair src = std::make_pair((int)((entity.getPosition(false) - 160.f)/20.f), (int)((entity.getPosition(true) - 240.f)/20.f));
    Pair dest = std::make_pair((int)((posAspen.getPosition(false) - 120.f)/20.f), (int)((posAspen.getPosition(true) - 220.f)/20.f));

    aStarSearch(grid, src, dest);

    float x = pathY() - (float)src.second;
    float y = pathX() - (float)src.first;

    sf::Vector2f movement (x, y);
    movement *= entity.getSpeed() * deltaTime.asSeconds();

    entity.moveEntity(movement.x, movement.y);
}

void Party::updateVIH(Entity &entity, sf::Time deltaTime){

    float realDeltaX = vectorVIH.x * entity.getSpeed() * 100.f * deltaTime.asSeconds();
    float realDeltaY = vectorVIH.y * entity.getSpeed() * 100.f * deltaTime.asSeconds();

    if(entity.getPosition(true) < 190.f || entity.getPosition(true) > 990.f)
        entity.moveEntity(-realDeltaX, realDeltaY);
    else if(entity.getPosition(false) < 110.f || entity.getPosition(false) > 510.f)
        entity.moveEntity(realDeltaX, -realDeltaY);
    else
        entity.moveEntity(realDeltaX, realDeltaY);

}

void Party::updateCOVID19(Entity &entity, sf::Time deltaTime, unsigned index){
    float deltaX = destinationMonster[index].x - entity.getPosition(true);
    float deltaY = destinationMonster[index].y - entity.getPosition(false);

    if(abs(deltaX) < abs(deltaY)){

        if(deltaY > -40.f && deltaY < 40.f){
            // on tire
            if(deltaX < 0.f)
                setProjectileRectangleShape(entity, 3); // shoot a gauche
            else
                setProjectileRectangleShape(entity, 1); // shoot a droite
        }
        else{
            //on se déplace sur le y du joueur
            entity.moveEntity(0, deltaY);

        }
    }
    else{

        if(deltaX > -20.f && deltaX < 20.f){
            // on tire
            if(deltaY < 0.f)
                setProjectileRectangleShape(entity, 0); // shoot en haut
            else
                setProjectileRectangleShape(entity, 2); //shoot en bas
        }
        else{
            //on se déplace sur l'axe X
            entity.moveEntity(deltaX, 0);
        }
    }
}

void Party::updateMonsters(sf::Time deltaTime){

    for(unsigned i = 0; i < walkMonst.size(); ++i) {
        if (walkMonst[i] && walkMonst[i]->getName() == "Tenia") {
            updateTenia(*walkMonst[i], deltaTime);

            sWalkingMonsters[i].setPosition(walkMonst[i]->getPosition(true) - 40.f, walkMonst[i]->getPosition(false) - 40.f);
        }
        else if(walkMonst[i] && walkMonst[i]->getName() == "Listeria"){
            updateListeria(*walkMonst[i], deltaTime);

            sWalkingMonsters[i].setPosition(walkMonst[i]->getPosition(true) - 40.f, walkMonst[i]->getPosition(false) - 40.f);
        }
        else if(walkMonst[i] && walkMonst[i]->getName() == "Blob"){
            updateBlob(*walkMonst[i], deltaTime);

            sWalkingMonsters[i].setPosition(walkMonst[i]->getPosition(true) - 40.f, walkMonst[i]->getPosition(false) - 40.f);
        }
        else if(walkMonst[i] && walkMonst[i]->getName() == "Cymothoa-exigua"){

            if (inActionMonster[i]) {
                actionTimeMonster[i] += deltaTime;
                updateCymothoaExigua(*walkMonst[i], deltaTime, i);

                if (actionTimeMonster[i] > sf::seconds(1.f)) {
                    actionTimeMonster[i] = sf::Time::Zero;
                    inActionMonster[i] = false;
                }
            } else {
                pauseTimeMonster[i] += deltaTime;

                if (pauseTimeMonster[i] > sf::seconds(1.5f)) {
                    pauseTimeMonster[i] = sf::Time::Zero;
                    inActionMonster[i] = true;

                    destinationMonster[i] = sf::Vector2f(posAspen.getPosition(true) + 20.f, posAspen.getPosition(false) + 54.f);
                }
            }

            sWalkingMonsters[i].setPosition(walkMonst[i]->getPosition(true) - 40.f, walkMonst[i]->getPosition(false) - 40.f);
        }
        else if(walkMonst[i] && walkMonst[i]->getName() == "VIH"){
            updateVIH(*walkMonst[i], deltaTime);

            sWalkingMonsters[i].setPosition(walkMonst[i]->getPosition(true) - 40.f, walkMonst[i]->getPosition(false) - 40.f);
        }
    }

    for(unsigned i = 0; i < flyMonst.size(); ++i) {
        if (flyMonst[i] && flyMonst[i]->getName() == "Grippe-Espagnole") {

            if (inActionMonster[i]) {
                actionTimeMonster[i] += deltaTime;
                updateGrippeEspagnole(*flyMonst[i], deltaTime, i);

                if (actionTimeMonster[i] > sf::seconds(2.f)) {
                    actionTimeMonster[i] = sf::Time::Zero;
                    inActionMonster[i] = false;
                }
            } else {
                pauseTimeMonster[i] += deltaTime;

                if (pauseTimeMonster[i] > sf::seconds(2.f)) {
                    pauseTimeMonster[i] = sf::Time::Zero;
                    inActionMonster[i] = true;

                    destinationMonster[i] = sf::Vector2f(posAspen.getPosition(true) + 20.f, posAspen.getPosition(false) + 54.f);
                }
            }

            sFlyingMonsters[i].setPosition(flyMonst[i]->getPosition(true) - 40.f, flyMonst[i]->getPosition(false) - 40.f);
        }
        else if (flyMonst[i] && flyMonst[i]->getName() == "Peste-Noire") {
            if (inActionMonster[i]) {
                actionTimeMonster[i] += deltaTime;
                updatePesteNoire(*flyMonst[i], deltaTime, i);

                if(actionTimeMonster[i] > sf::seconds(1.5f)){
                    actionTimeMonster[i] = sf::Time::Zero;
                    inActionMonster[i] = false;
                }
            }
            else{
                pauseTimeMonster[i] += deltaTime;

                if(pauseTimeMonster[i] > sf::seconds(2.f)){
                    pauseTimeMonster[i] = sf::Time::Zero;
                    inActionMonster[i] = true;

                    destinationMonster[i] = sf::Vector2f (posAspen.getPosition(true), posAspen.getPosition(false));
                }
            }

            sFlyingMonsters[i].setPosition(flyMonst[i]->getPosition(true) - 40.f, flyMonst[i]->getPosition(false) - 40.f);
        }
        else if(flyMonst[i] && flyMonst[i]->getName() == "H1N1"){
            updateH1N1(*flyMonst[i], deltaTime);

            sFlyingMonsters[i].setPosition(flyMonst[i]->getPosition(true) - 40.f, flyMonst[i]->getPosition(false) - 40.f);
        }
        else if (flyMonst[i] && flyMonst[i]->getName() == "Covid-19") {
            if (inActionMonster[i]) {
                actionTimeMonster[i] += deltaTime;
                updateCOVID19(*flyMonst[i], deltaTime, i);

                if(actionTimeMonster[i] > sf::seconds(1.f)){
                    actionTimeMonster[i] = sf::Time::Zero;
                    inActionMonster[i] = false;
                }
            }
            else{
                pauseTimeMonster[i] += deltaTime;

                if(pauseTimeMonster[i] > sf::seconds(1.f)){
                    pauseTimeMonster[i] = sf::Time::Zero;
                    inActionMonster[i] = true;

                    destinationMonster[i] = sf::Vector2f (posAspen.getPosition(true), posAspen.getPosition(false));
                }
            }

            sFlyingMonsters[i].setPosition(flyMonst[i]->getPosition(true) - 40.f, flyMonst[i]->getPosition(false) - 40.f);
        }
    }
}

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
    
    chestsCollider.clean();
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
    
    trapCollider.clean();
    trapCollider.pushBodies(sTrap.begin(), sTrap.end());
}

sf::Texture* Party::selectProjectileTexture(const Entity& entity, unsigned orient){
    unsigned idProjectile;
    if(entity.getName() == "Aspen"){

        if(entity.getInventoryStuff(4)){
            switch(entity.getInventoryStuff(4)->getId()){
                case 35:
                    idProjectile = 2;
                    break;

                case 36:
                    idProjectile = 2;
                    break;

                case 37:
                    idProjectile = 2;
                    break;

                case 38:
                    idProjectile = 3;
                    break;

                case 39:
                    idProjectile = 3;
                    break;

                case 40:
                    idProjectile = 3;
                    break;

                default:
                    break;
            }
        }
        else
            idProjectile = 1;
    }
    else
        idProjectile = 0;

    switch(orient){
        case 0:
            return getTexture("ProjectileN" + std::to_string(idProjectile));
            break;

        case 1:
            return getTexture("ProjectileE" + std::to_string(idProjectile));
            break;

        case 2:
            return getTexture("ProjectileS" + std::to_string(idProjectile));
            break;

        case 3:
            return getTexture("ProjectileW" + std::to_string(idProjectile));
            break;

        default:
            return nullptr;
            break;
    }
}

void Party::setProjectileRectangleShape(const Entity& entity, unsigned orient){ // A appeler quand une entity tire ou si le joeur appui sur une touche de tir

    sf::RectangleShape proj;
    Position<float> posProjectile(0.f, 0.f);
    unsigned type = entity.getName() == "Aspen" ? 0 : 1;
    unsigned speed = entity.getSpeed() + 10;
    unsigned nbCollision = 1;
    float attack = entity.getAttack();

    switch(orient){
        case 0:
            proj.setSize({10.f, 40.f});
            proj.setTexture(selectProjectileTexture(entity, orient));

            if(type == 0)
                posProjectile.setPosition(posAspen.getPosition(true) + ((40.f - proj.getGlobalBounds().width)/2.f), posAspen.getPosition(false) + (80.f*(2.f/3.f) - proj.getGlobalBounds().height));
            else
                posProjectile.setPosition(entity.getPosition(true) - proj.getGlobalBounds().width/2.f, entity.getPosition(false) - 40.f - proj.getGlobalBounds().height);

            proj.setPosition(posProjectile.getPosition(true), posProjectile.getPosition(false));
            sProjectiles.emplace(new Projectile(posProjectile.getPosition(true), posProjectile.getPosition(false), orient, type, speed, nbCollision, attack), proj);
            break;

        case 1:
            proj.setSize({40.f, 10.f});
            proj.setTexture(selectProjectileTexture(entity, orient));

            if(type == 0)
                posProjectile.setPosition(posAspen.getPosition(true) + 40.f, posAspen.getPosition(false) + (80.f*(5.f/6.f) - (proj.getGlobalBounds().height/2.f)));
            else
                posProjectile.setPosition(entity.getPosition(true) + 40.f, entity.getPosition(false) + proj.getGlobalBounds().height / 2.f);

            proj.setPosition(posProjectile.getPosition(true), posProjectile.getPosition(false));
            sProjectiles.emplace(new Projectile(posProjectile.getPosition(true), posProjectile.getPosition(false), orient, type, speed, nbCollision, attack), proj);
            break;

        case 2:
            proj.setSize({10.f, 40.f});
            proj.setTexture(selectProjectileTexture(entity, orient));

            if(type == 0)
                posProjectile.setPosition(posAspen.getPosition(true) + ((40.f - proj.getGlobalBounds().width)/2.f), posAspen.getPosition(false) + 80.f);
            else
                posProjectile.setPosition(entity.getPosition(true) - proj.getGlobalBounds().width/2.f, entity.getPosition(false) + 40.f);

            proj.setPosition(posProjectile.getPosition(true), posProjectile.getPosition(false));
            sProjectiles.emplace(new Projectile(posProjectile.getPosition(true), posProjectile.getPosition(false), orient, type, speed, nbCollision, attack), proj);
            break;

        case 3:
            proj.setSize({40.f, 10.f});
            proj.setTexture(selectProjectileTexture(entity, orient));

            if(type == 0)
                posProjectile.setPosition(posAspen.getPosition(true) - proj.getGlobalBounds().width, posAspen.getPosition(false) + (80.f*(5.f/6.f) - (proj.getGlobalBounds().height/2.f)));
            else
                posProjectile.setPosition(entity.getPosition(true) - 40.f - proj.getGlobalBounds().width, entity.getPosition(false) + proj.getGlobalBounds().height / 2.f);

            proj.setPosition(posProjectile.getPosition(true), posProjectile.getPosition(false));
            sProjectiles.emplace(new Projectile(posProjectile.getPosition(true), posProjectile.getPosition(false), orient, type, speed, nbCollision, attack), proj);
            break;

        default:
            break;
    }
}

void Party::updateProjectile(){
    for(auto &p :sProjectiles){
        if(p.first){
            p.first->update();
            p.second.setPosition(p.first->getProjectilePosition(true), p.first->getProjectilePosition(false));
        }
    }
}

void Party::drawProjectile(){
    for(auto &p : sProjectiles){
        if(p.first) {
            mWindow.draw(p.second);
        }
    }
}

void Party::setRectangleShapeForCurrentRoom(){

    Room* curRoom = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false));

    if (curRoom) {
        setWall();
        setHole(*curRoom);
        if(curRoom->getMonsters().empty())
            setDoorOpenRectangleShape(*curRoom);
        else
            setDoorCloseRectangleShape(*curRoom);
        setRockChoice(*curRoom);
        setRockRectangleShape(*curRoom);
        setMonsterRectangleShape(*curRoom);
        setChestRectangleShape(*curRoom);
        setTrapRectangleShape(*curRoom);
        setLifeRectangleShape();
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

sf::Color Party::setItemLvl(unsigned id){
    switch(id%3){
        case 0:
            return sf::Color::Yellow;
            break;
        case 1:
            return sf::Color::Magenta;
            break;
        case 2:
            return sf::Color::White;
            break;

        default:
            return sf::Color::Transparent;
            break;
    }
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
    
    sf::Text txt;
    txt.setFont(objectsFont);
    txt.setCharacterSize(10);
    txt.setFillColor(sf::Color::White);
    txt.setOutlineColor(sf::Color::Black);
    txt.setOutlineThickness(1.f);
    
    objectsNumber.clear();
    bagItem.clear();
	stuffItem.clear();

    unsigned id;
    Object::Type type;

    for (unsigned i = 0; i < playerBagSize; ++i){
        sf::Sprite item;
        const Object* object = Aspen.getInventoryObject(i);

        if(object){
            item.setPosition(arch.itemBag[i][0], arch.itemBag[i][1]);

            id = object->getId();
            type = object->getType();

            if(type == Object::Type::potion){
                item.setTexture(*getTexture(std::to_string(id)));
                item.scale(50.f/128.f, 50.f/128.f);
            }
            if(type == Object::Type::monsterLoot){
                item.setTexture(*getTexture(std::to_string(id)));
                item.scale(50.f/64.f, 50.f/64.f);
            }
            if(type == Object::Type::helmet){
                item.setColor(setItemLvl(id));
                if(id < 14)
                    item.setTexture(*getTexture("11"));
                else
                    item.setTexture(*getTexture("14"));
                item.scale(50.f/128.f, 50.f/128.f);
            }
            if(type == Object::Type::chestplate){
                item.setColor(setItemLvl(id));
                if(id < 20)
                    item.setTexture(*getTexture("17"));
                else
                    item.setTexture(*getTexture("20"));
                item.scale(50.f/128.f, 50.f/128.f);
            }
            if(type == Object::Type::leggings){
                item.setColor(setItemLvl(id));
                if(id < 26)
                    item.setTexture(*getTexture("23"));
                else
                    item.setTexture(*getTexture("26"));
                item.scale(50.f/128.f, 50.f/128.f);
            }
            if(type == Object::Type::boots){
                item.setColor(setItemLvl(id));
                if(id < 32)
                    item.setTexture(*getTexture("29"));
                else
                    item.setTexture(*getTexture("32"));
                item.scale(50.f/128.f, 50.f/128.f);
            }
            if(type == Object::Type::projectile){
                item.setColor(setItemLvl(id));
                if(id < 38)
                    item.setTexture(*getTexture("35"));
                else
                    item.setTexture(*getTexture("38"));
                item.scale(50.f/64.f, 50.f/64.f);
            }
            if(type == Object::Type::amulet){
                item.setColor(setItemLvl(id));
                if(id < 44)
                    item.setTexture(*getTexture("41"));
                else
                    item.setTexture(*getTexture("44"));
                item.scale(50.f/128.f, 50.f/128.f);
            }

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
            item.setPosition(arch.itemBag[i][0], arch.itemBag[i][1]);
            item.setTexture(*getTexture("Nothing"));
            bagItem.emplace(i, item);
        }
    }

    for (unsigned i = 0; i < playerStuffSize; ++i){
        sf::Sprite item;
        const Object* object = Aspen.getInventoryStuff(i);

        if(object){
            item.setPosition(arch.itemStuff[i][0], arch.itemStuff[i][1]);

            id = object->getId();
            type = object->getType();

            item.setColor(setItemLvl(id));
            if(type == Object::Type::helmet){
                if(id < 14)
                    item.setTexture(*getTexture("11"));
                else
                    item.setTexture(*getTexture("14"));
                item.scale(50.f/128.f, 50.f/128.f);
            }
            if(type == Object::Type::chestplate){
                if(id < 20)
                    item.setTexture(*getTexture("17"));
                else
                    item.setTexture(*getTexture("20"));
                item.scale(50.f/128.f, 50.f/128.f);
            }
            if(type == Object::Type::leggings){
                if(id < 26)
                    item.setTexture(*getTexture("23"));
                else
                    item.setTexture(*getTexture("26"));
                item.scale(50.f/128.f, 50.f/128.f);
            }
            if(type == Object::Type::boots){
                if(id < 32)
                    item.setTexture(*getTexture("29"));
                else
                    item.setTexture(*getTexture("32"));
                item.scale(50.f/128.f, 50.f/128.f);
            }
            if(type == Object::Type::projectile){
                if(id < 38)
                    item.setTexture(*getTexture("35"));
                else
                    item.setTexture(*getTexture("38"));
                item.scale(50.f/64.f, 50.f/64.f);
            }
            if(type == Object::Type::amulet){
                if(id < 44)
                    item.setTexture(*getTexture("41"));
                else
                    item.setTexture(*getTexture("44"));
                item.scale(50.f/128.f, 50.f/128.f);
            }

            stuffItem.emplace(i, item);
        }
        else{
            item.setPosition(arch.itemStuff[i][0], arch.itemStuff[i][1]);
            item.setTexture(*getTexture("Nothing"));
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
    sf::Sprite item;
    Chest* chest = curRoom.getChest();

    chestInventory.setSize({480.f, 280.f});
    chestInventory.setPosition(arch.chestInventory[0], arch.chestInventory[1]);
    chestInventory.setTexture(getTexture("ChestInventory"));

    unsigned id;
    Object::Type type;

    sf::Text txt;
    txt.setFont(objectsFont);
    txt.setCharacterSize(10);
    txt.setFillColor(sf::Color::White);
    txt.setOutlineColor(sf::Color::Black);
    txt.setOutlineThickness(1.f);

    if(chest){
        chestItem.clear();
        chestObjectNumber.clear();

        for (unsigned i = 0; i < chestSize; ++i){
            const Object* object = chest->getItem(i);
            sf::Sprite item;

            if(object){
                item.setPosition(arch.itemChest[i][0], arch.itemChest[i][1]);

                id = object->getId();
                type = object->getType();

                if(type == Object::Type::potion){
                    item.setTexture(*getTexture(std::to_string(id)));
                    item.scale(50.f/128.f, 50.f/128.f);
                }
                if(type == Object::Type::monsterLoot){
                    item.setTexture(*getTexture(std::to_string(id)));
                    item.scale(50.f/64.f, 50.f/64.f);
                }
                if(type == Object::Type::helmet){
                    item.setColor(setItemLvl(id));
                    if(id < 14)
                        item.setTexture(*getTexture("11"));
                    else
                        item.setTexture(*getTexture("14"));
                    item.scale(50.f/128.f, 50.f/128.f);
                }
                if(type == Object::Type::chestplate){
                    item.setColor(setItemLvl(id));
                    if(id < 20)
                        item.setTexture(*getTexture("17"));
                    else
                        item.setTexture(*getTexture("20"));
                    item.scale(50.f/128.f, 50.f/128.f);
                }
                if(type == Object::Type::leggings){
                    item.setColor(setItemLvl(id));
                    if(id < 26)
                        item.setTexture(*getTexture("23"));
                    else
                        item.setTexture(*getTexture("26"));
                    item.scale(50.f/128.f, 50.f/128.f);
                }
                if(type == Object::Type::boots){
                    item.setColor(setItemLvl(id));
                    if(id < 32)
                        item.setTexture(*getTexture("29"));
                    else
                        item.setTexture(*getTexture("32"));
                    item.scale(50.f/128.f, 50.f/128.f);
                }
                if(type == Object::Type::projectile){
                    item.setColor(setItemLvl(id));
                    if(id < 38)
                        item.setTexture(*getTexture("35"));
                    else
                        item.setTexture(*getTexture("38"));
                    item.scale(50.f/64.f, 50.f/64.f);
                }
                if(type == Object::Type::amulet){
                    item.setColor(setItemLvl(id));
                    if(id < 44)
                        item.setTexture(*getTexture("41"));
                    else
                        item.setTexture(*getTexture("44"));
                    item.scale(50.f/128.f, 50.f/128.f);
                }

                chestItem.emplace(i, item);

                if (object->getObjectNumber() > 1){
                    txt.setString(std::to_string(object->getObjectNumber()));

                    sf::FloatRect bounds = txt.getLocalBounds();
                    txt.setOrigin({bounds.width, bounds.height});
                    txt.setPosition(arch.itemBag[i][0] + 48.f, arch.itemBag[i][1] + 48.f);

                    objectsNumber.emplace(i, txt);
                }
            }
            else{
                item.setPosition(arch.itemChest[i][0], arch.itemChest[i][1]);
                item.setTexture(*getTexture("Nothing"));
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
                    scrollingValue = 3;
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

                    if(chestOpen){
                        txt.setString("Add to chest");
                        txt.setPosition(arch.itemBag[inventoryIndex][0] + 52.f, arch.itemBag[inventoryIndex][1] + 30.f);
                        textScrolling.push_back(txt);

                        scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                        bounds = txt.getGlobalBounds();
                        scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                        rectangleShapeScrolling.push_back(scrollMenu);
                    }
                }
                else if(Aspen.getInventoryObject(inventoryIndex)->getType() == Object::Type::potion){
                    scrollingValue = 4;
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

                    if(chestOpen){
                        txt.setString("Add to chest");
                        txt.setPosition(arch.itemBag[inventoryIndex][0] + 52.f, arch.itemBag[inventoryIndex][1] + 45.f);
                        textScrolling.push_back(txt);

                        scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                        bounds = txt.getGlobalBounds();
                        scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                        rectangleShapeScrolling.push_back(scrollMenu);
                    }
                }
                else{ // Si c'est un equipement
                    scrollingValue = 4;
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

                    if(chestOpen){
                        txt.setString("Add to chest");
                        txt.setPosition(arch.itemBag[inventoryIndex][0] + 52.f, arch.itemBag[inventoryIndex][1] + 45.f);
                        textScrolling.push_back(txt);

                        scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                        bounds = txt.getGlobalBounds();
                        scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                        rectangleShapeScrolling.push_back(scrollMenu);
                    }
                }
            }
            else{
                scrollingMenuOpen = false;
            }
            break;

        case 3: { // ajouter a l'inventaire(enlever du coffre) seulement s'il y a un object, sinon fermer le scrollingMenu

            if (donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getChest()->getItem(inventoryIndex)) {
                scrollingValue = 1;
                txt.setString("Add to inventory");
                txt.setPosition(arch.itemChest[inventoryIndex][0] + 52.f, arch.itemChest[inventoryIndex][1]);
                textScrolling.push_back(txt);

                scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                bounds = txt.getGlobalBounds();
                scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                rectangleShapeScrolling.push_back(scrollMenu);
            } else
                scrollingMenuOpen = false;
            break;
        }

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

                case sf::Keyboard::Return:{// on appui sur entrer on applique le choix selectionné

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

							Chest *chest = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getChest();
							chest->removeFromChest(inventoryIndex);
                            setInventoryItem();
                            setChestItem(*donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false)));
						    scrollingMenuOpen = false;
						}
						else if(action == std::string("Add to chest")){

						    Chest *chest = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getChest();
						    chest->placeInChest(inventoryIndex);
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
						if (inventoryIndex != 0){
							--inventoryIndex;
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
                        if(inventoryIndex < 4){
                            inventoryValue = 2;
                            inventoryIndex = playerBagSize - 1;
                        }
						else if (inventoryIndex > 3){
							inventoryIndex -= 4;
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
						if (inventoryIndex < chestSize - 1)
							++inventoryIndex;
					}
					break;

				case sf::Keyboard::D: // on va a droite dans l'inventaire
					if(inventoryValue == 2){
						if(inventoryIndex < 5){
							inventoryIndex += 5;
						}
						else if (chestOpen){
							inventoryValue = 3;
							inventoryIndex = 0;
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
					else if(inventoryValue == 3){ // dans le coffre
						if(inventoryIndex < 16){
							inventoryIndex += 4;
						}
					//	else if(inventoryIndex > 15 && inventoryIndex < chestSize - 1){ // 4 dernières cases de droite seulement
					//	    ++inventoryIndex;
					//	}
					}
					break;

				case sf::Keyboard::Space:{ // on ouvre les menu déroulant

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
                    mIsShootingUp = false;
                    mIsShootingDown = false;
                    mIsShootingLeft = false;
                    mIsShootingRight = false;
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

        for(auto &n : chestObjectNumber)
            mWindow.draw(n.second);
		
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

void Party::updateException(){
    sf::Event event;
    
    while (mWindow.pollEvent(event)){
        if (event.type == sf::Event::Closed){
            mWindow.close();
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
            inventoryOpen = false;
            scrollingMenuOpen = false;
            moveObjectOpen = false;
            chestOpen = false;
            mIsMovingUp = false;
            mIsMovingDown = false;
            mIsMovingLeft = false;
            mIsMovingRight = false;
            mIsShootingUp = false;
            mIsShootingDown = false;
            mIsShootingLeft = false;
            mIsShootingRight = false;
            exceptionState = false;
        }
    }
}

void Party::drawException(){
    sf::RectangleShape rect ({400.f, 150.f});
    rect.setFillColor(sf::Color::White);
    rect.setOrigin({200.f, 75.f});
    rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);
    
    sf::Text exception;
    exception.setFillColor(sf::Color::Black);
    exception.setFont(statsFont);
    exception.setCharacterSize(15);
    exception.setString(exceptionText);
    
    sf::FloatRect textBounds = exception.getLocalBounds();
    exception.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    exception.setPosition(rect.getPosition());
    
    mWindow.draw(rect);
    mWindow.draw(exception);
}

void Party::reloadRoom(){

    for(auto p = sProjectiles.begin(); p != sProjectiles.end();){
        if(p->first)
            delete p->first;
        p = sProjectiles.erase(p);
    }

	Room* curRoom = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false));
	loadSprites(curRoom->getStringType());
	
	trapCollider.clean();
	wallsCollider.clean();
	holesCollider.clean();
	rocksCollider.clean();
	doorsCollider.clean();
	flyingMonstersCollider.clean();
	walkingMonstersCollider.clean();
    lootCollider.clean();
	chestsCollider.clean();

    sLoot.clear();
    Loots.clear();
    hitBoxLoots.clear();
	
	setSpritesForCurrentRoom();
    setRectangleShapeForCurrentRoom();
	
	setChestItem(*curRoom);
    
    setAStar(*curRoom);
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

	    // Walls
    playerCol.checkCollision(wallsCollider, colDirection, 0.f);

        // Monsters
    std::vector<std::pair<std::size_t, std::size_t>> collisions;

    std::vector<sf::Vector2f> flyMonstPos;

    for (const auto& m : sFlyingMonsters)
        flyMonstPos.push_back(m.getPosition());

    if(!flyMonst.empty() && playerCol.checkCollision(flyingMonstersCollider, collisions, 0.5f)){
        for (auto c : collisions) {
            if (flyMonst[c.second]) {
                Aspen.removeLife((int) (flyMonst[c.second]->getAttack() * (1.f - (Aspen.getDefence() - 100.f) / 100.f)));
            }
        }
        if(Aspen.getLife() < 0)
            throw std::range_error ("Game Over You died");
    }


    std::vector<sf::Vector2f> walkMonstPos;

    for (const auto& m : sWalkingMonsters)
        walkMonstPos.push_back(m.getPosition());

    if(!walkMonst.empty() && playerCol.checkCollision(walkingMonstersCollider, collisions, 0.5f)){
        for (auto c : collisions) {
            if (walkMonst[c.second]) {
                Aspen.removeLife((int) (walkMonst[c.second]->getAttack() * (1.f - (Aspen.getDefence() - 100.f) / 100.f)));
            }
        }
        if(Aspen.getLife() < 0)
            throw std::range_error ("Game Over You died");
    }

        // Loots
    std::vector<std::pair<std::size_t, std::size_t>> lootCollisions;

    if(donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getMonsters().empty() && !Aspen.inventoryEmpty()){
        if(playerCol.checkCollision(lootCollider, lootCollisions, 0.f)){
            for(auto c : lootCollisions){
                try{ // pour laisser les objets au sol, il faut mettre tout le bloc dans le if
                    Aspen.addInventoryObject(sLoot[c.second], 1);
                }
                catch (std::logic_error& err){
                    exceptionState = true;
                    exceptionText = std::string(err.what());
                }
                sLoot.erase(sLoot.begin() + c.second);
                Loots.erase(Loots.begin() + c.second);
                hitBoxLoots.erase(hitBoxLoots.begin() + c.second);

                setInventoryItem();

                lootCollider.clean();
                lootCollider.pushBodies(hitBoxLoots.begin(), hitBoxLoots.end());
            }
        }
    }


        // Collision for flying Monsters
    flyingMonstersCollider.checkCollision(wallsCollider, 0.f);
        // Monsters fly
    for (unsigned i = 0; i < sFlyingMonsters.size(); ++i){
        flyMonst[i]->moveEntity(sFlyingMonsters[i].getPosition().x - flyMonstPos[i].x, sFlyingMonsters[i].getPosition().y - flyMonstPos[i].y);
    }

        // Collision for walking Monsters
    walkingMonstersCollider.checkCollision(holesCollider, 0.f);
    walkingMonstersCollider.checkCollision(wallsCollider, 0.f);
    walkingMonstersCollider.checkCollision(rocksCollider, 0.f);
        // Monsters walk
    for (unsigned i = 0; i < sWalkingMonsters.size(); ++i){
        walkMonst[i]->moveEntity(sWalkingMonsters[i].getPosition().x - walkMonstPos[i].x, sWalkingMonsters[i].getPosition().y - walkMonstPos[i].y);
    }

    if (!Aspen.entityCanFly()){
		playerCol.checkCollision(holesCollider, colDirection, 0.f);
        playerCol.checkCollision(rocksCollider, colDirection, 0.f);
	}

	if(playerCol.checkCollision(chestsCollider, colDirection, 0.f)){
	    inventoryOpen = true;
	    chestOpen = true;
		inventoryValue = 2;
        inventoryIndex = 0;
	}

	if (donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getMonsters().empty() && !sTrap.empty())
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
	if (donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getMonsters().empty() && playerCol.checkCollision(doorsCollider, colDirection, 0.f))
	{
		if (colDirection.y < 0.f && door[0] && door[0]->getOpen()){
			posDonjon.move(-1, 0);
            posAspen.setPosition(arch.PlayerS[0], arch.PlayerS[1]);
            aspenAnimated.setPosition(posAspen.getPosition(true), posAspen.getPosition(false));
			reloadRoom();
		}
		else if (colDirection.y > 0.f && door[2] && door[2]->getOpen()){
			posDonjon.move(1, 0);
            posAspen.setPosition(arch.PlayerN[0], arch.PlayerN[1]);
            aspenAnimated.setPosition(posAspen.getPosition(true), posAspen.getPosition(false));
			reloadRoom();
		}
		
		if (colDirection.x < 0.f && door[3] && door[3]->getOpen()){
			posDonjon.move(0, -1);
            posAspen.setPosition(arch.PlayerE[0], arch.PlayerE[1]);
            aspenAnimated.setPosition(posAspen.getPosition(true), posAspen.getPosition(false));
			reloadRoom();
		}
		else if (colDirection.x > 0.f && door[1] && door[1]->getOpen()){
			posDonjon.move(0, 1);
            posAspen.setPosition(arch.PlayerW[0], arch.PlayerW[1]);
            aspenAnimated.setPosition(posAspen.getPosition(true), posAspen.getPosition(false));
			reloadRoom();
		}
	}
	else{
        playerCol.checkCollision(doorsCollider, colDirection, 0.f);
	}
	
	sf::Vector2f posEnd = sPlayerCol.getPosition();
		
	posAspen.move(posEnd.x - posBegin.x, posEnd.y - posBegin.y);
    aspenAnimated.setPosition(posAspen.getPosition(true), posAspen.getPosition(false));
}

void Party::removeLife(Projectile *projectile, Entity *entityShoot){
    if(entityShoot && projectile){
        if(projectile->getProjectileType() == Projectile::EntityType::monster){ // Tiré par un monstre
            if(entityShoot->getName() == "Aspen")
                Aspen.removeLife(projectile->getAttack());
        }
        if(projectile->getProjectileType() == Projectile::EntityType::player){
            entityShoot->removeLife(projectile->getAttack());
        }
    }
    updateLife();
}

void Party::projectileCollision(){
    
    Room *curRoom = donjon.getRoom(posDonjon.getPosition(true),posDonjon.getPosition(false));
    
    auto p = sProjectiles.begin();
    while (p != sProjectiles.end()){
        if(p->first){
            Collider projCol (p->second);
            
                // Rocks
            
            std::vector<std::pair<std::size_t, std::size_t>> collisions;
            bool resetCollider = false;
            
            if (projCol.checkCollision(rocksCollider, collisions, 0.f)){
                p = sProjectiles.erase(p);
                
                std::vector<Rock>& rocks = curRoom->getRocks();
                
                for (auto c : collisions){
                    if (--rocks[c.second].life == 0){
                        resetCollider = true;
                    }
                }
                
                if (resetCollider){
                    setRockRectangleShape(*curRoom);
                    setAStar(*curRoom);
                }
                
                continue;
            }
            
                // Chests
            
            if (projCol.checkCollision(chestsCollider, 0.f)){
                p = sProjectiles.erase(p);
                continue;
            }
                // Entity
            std::vector<std::pair<std::size_t, std::size_t>> projCollisions;
            resetCollider = false;

            if (projCol.checkCollision(walkingMonstersCollider, projCollisions, 0.f)) {

                for (auto &c : projCollisions){
                    removeLife(p->first, walkMonst[c.second]);

                    if (walkMonst[c.second]->getLife() <= 0) {

                        setLootOnTheFloor(*walkMonst[c.second]);

                        std::vector<Entity*>& roomMonsters = curRoom->getMonsters();
                        auto found = std::find(roomMonsters.begin(), roomMonsters.end(), walkMonst[c.second]);
                        delete walkMonst[c.second];
                        *found = nullptr;
                        roomMonsters.erase(found);

                        walkMonst.erase(walkMonst.begin() + c.second);
                        destinationMonster.erase(destinationMonster.begin() + flyMonst.size() + c.second);
                        actionTimeMonster.erase(actionTimeMonster.begin() + flyMonst.size() + c.second);
                        pauseTimeMonster.erase(pauseTimeMonster.begin() + flyMonst.size() + c.second);
                        inActionMonster.erase(inActionMonster.begin() + flyMonst.size() + c.second);

                        resetCollider = true;
                    }
                }

                if (resetCollider) {
                    setMonsterRectangleShape(*curRoom);
                    if(donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getMonsters().empty())
                        setDoorOpenRectangleShape(*curRoom);
                }

                p = sProjectiles.erase(p);
                projCollisions.clear();
                continue;
            }

            projCollisions.resize(0);
            resetCollider = false;

            if(projCol.checkCollision(flyingMonstersCollider, projCollisions, 0.f)){

                for (auto &c : projCollisions){
                    removeLife(p->first, flyMonst[c.second]);

                    if (flyMonst[c.second]->getLife() <= 0) {

                        setLootOnTheFloor(*flyMonst[c.second]);

                        std::vector<Entity*>& roomMonsters = curRoom->getMonsters();
                        auto found = std::find(roomMonsters.begin(), roomMonsters.end(), flyMonst[c.second]);
                        delete flyMonst[c.second];
                        *found = nullptr;
                        roomMonsters.erase(found);

                        flyMonst.erase(flyMonst.begin() + c.second);
                        destinationMonster.erase(destinationMonster.begin() + c.second);
                        actionTimeMonster.erase(actionTimeMonster.begin() + c.second);
                        pauseTimeMonster.erase(pauseTimeMonster.begin() + c.second);
                        inActionMonster.erase(inActionMonster.begin() + c.second);

                        resetCollider = true;
                    }
                }

                if (resetCollider) {
                    setMonsterRectangleShape(*curRoom);
                    if(donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getMonsters().empty())
                        setDoorOpenRectangleShape(*curRoom);
                }

                p = sProjectiles.erase(p);
                projCollisions.clear();
                continue;
            }

            // Aspen

            sf::RectangleShape sPlayerCol ({(aspenAnimated.getLocalBounds()).width, (aspenAnimated.getLocalBounds()).height / 2.f});
            sPlayerCol.setOrigin({0.f, sPlayerCol.getSize().y});
            sPlayerCol.setPosition(posAspen.getPosition(true), posAspen.getPosition(false) + (aspenAnimated.getLocalBounds()).height);
            sPlayerCol.move(0.f, (aspenAnimated.getLocalBounds()).height / 6.f);
            Collider playerCol (sPlayerCol);

            if (projCol.checkCollision(playerCol, 0.f)){
                removeLife(p->first, &Aspen);

                p = sProjectiles.erase(p);
                continue;
            }

            // Walls
            if(projCol.checkCollision(wallsCollider, 0.f)){
                p = sProjectiles.erase(p);
                continue;
            }

                // Doors
            if (projCol.checkCollision(doorsCollider, 0.f)){
                p = sProjectiles.erase(p);
                continue;
            }
        }
        
        ++p;
    }

    if (Aspen.getLife() <= 0.f){
        throw std::range_error ("Game over you died !");
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

    if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;

    if (key == sf::Keyboard::Q)
        mIsMovingLeft = isPressed;

    if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;

    if (key == sf::Keyboard::Up)
        mIsShootingUp = isPressed;

    if (key == sf::Keyboard::Left)
        mIsShootingLeft = isPressed;

    if (key == sf::Keyboard::Right)
        mIsShootingRight = isPressed;

    if (key == sf::Keyboard::Down)
        mIsShootingDown = isPressed;

    if (isPressed && key == sf::Keyboard::E){
        inventoryOpen = true;
        inventoryValue = 2;
        inventoryIndex = 0;
    }
}

void Party::updateForShooting(sf::Time deltaTime){

    aspenAttackSpeed = sf::seconds(1.f / Aspen.getAttackSpeed());
    
    if (mIsShootingUp || mIsShootingDown || mIsShootingRight || mIsShootingLeft){
        elapsedTime += deltaTime;
        
        while (elapsedTime > aspenAttackSpeed){ // seulement actif losqu'on appuie sur une touche de tir
            elapsedTime -= aspenAttackSpeed;

            if(mIsShootingUp){
                setProjectileRectangleShape(Aspen, 0);
            }
            else if(mIsShootingDown){
                setProjectileRectangleShape(Aspen, 2);
            }
            else if(mIsShootingRight){
                setProjectileRectangleShape(Aspen, 1);
            }
            else if(mIsShootingLeft){
                setProjectileRectangleShape(Aspen, 3);
            }
        }
    }
}

void Party::update(sf::Time deltaTime){

	sf::Vector2f movement(0.f, 0.f);
	PlayerSpeed = Aspen.getSpeed() + 130.f;

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

    updateForShooting(deltaTime);

	aspenAnimated.play(*currentAnimation);
	posAspen.move(movement.x * deltaTime.asSeconds(), movement.y * deltaTime.asSeconds());
    aspenAnimated.setPosition(posAspen.getPosition(true), posAspen.getPosition(false));

	if (noKeyWasPressed){
		aspenAnimated.stop();
	}
	noKeyWasPressed = true;

	aspenAnimated.update(deltaTime);
    updateMonsters(deltaTime);
    updateProjectile();
	entityCollision();
    projectileCollision();
}

void Party::render(){

    mWindow.clear();
    
    mWindow.draw(sRoom);

    for(const auto &r : sRocks)
        mWindow.draw(r);
    
    for(const auto &r : sNoRocks)
        mWindow.draw(r);

    for(const auto &f : sFrames)
        mWindow.draw(f);

    for(const auto &d : sDoors)
        mWindow.draw(d);

    for(const auto &c : sChest)
        mWindow.draw(c);

    if(donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getMonsters().empty())
        for(const auto &t : sTrap)
            mWindow.draw(t);
    
    drawProjectile();

    drawLootOnTheFloor();

   for(const auto &m : sWalkingMonsters)
        mWindow.draw(m);

   for(const auto &m : sFlyingMonsters)
        mWindow.draw(m);
    
    mWindow.draw(aspenAnimated);
    
    if(inventoryOpen) {
        if(chestOpen){
            drawChestInventory();
        }
        drawPlayerInventory();
    }

    mWindow.draw(sMaxLife);
    mWindow.draw(sLife);
    
    if(exceptionState){
        drawException();
    }
    
    mWindow.display();
}
