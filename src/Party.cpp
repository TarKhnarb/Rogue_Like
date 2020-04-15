#include "Party.h"

Party::Party():
        mWindow(sf::VideoMode(640, 480), "Aspen's Adventure"){

    loadTextures();
    loadSprites("Aspen");
    loadSprites("Rock");

    sPlayer = getSprite("sAspenF");
    sPlayer.setPosition(320.f, 240.f);

    sRock.setTexture(getTexture("Rock1"));
    sRock.setPosition(100.f, 100.f);
}

Party::~Party(){
    for(auto &t : textures){
        delete t.second;
        t.second = nullptr;
    }
}

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

bool Party::testCollision(sf::FloatRect s1, sf::FloatRect s2){
    if(s1.intersects(s2))
        return false;
    else
        return true;
}
/*
sf::Vector2 Party::setPositionCollision(sf::FloatRect s1, sf::FloatRect s2){
    if(s1.intersects(s2) && (s1.left > s2.left)){ // s1 a droite de s2

    }
    if(s1.intersects(s2) && (s1.left < s2.left)){ // s1 a gauche de s2

    }
    if(s1.intersects(s2) && (s1.top > s2.top)){ // s1 au dessus de s2

    }
    if(s1.intersects(s2) && (s1.top < s2.top)){ // s1 en dessous de s2

    }
}*/
// sf::Rect< T >::height/left/top/width
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

    sf::FloatRect test = sPlayer.getGlobalBounds();
    if(mIsMovingUp)
        test.top -= PlayerSpeed;
    if(mIsMovingDown)
        test.top += PlayerSpeed;
    if(mIsMovingLeft)
        test.left -= PlayerSpeed;
    if(mIsMovingRight)
        test.left += PlayerSpeed;

    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp && test.intersects(sRock.getGlobalBounds()))
        movement.y -= PlayerSpeed;

    if (mIsMovingDown && test.intersects(sRock.getGlobalBounds()))
        movement.y += PlayerSpeed;

    if (mIsMovingLeft && test.intersects(sRock.getGlobalBounds()))
        movement.x -= PlayerSpeed;

    if (mIsMovingRight && test.intersects(sRock.getGlobalBounds()))
        movement.x += PlayerSpeed;

    if(!testCollision(sPlayer.getGlobalBounds(), sRock.getGlobalBounds())){

    }

    sPlayer.move(movement * deltaTime.asSeconds());
}

void Party::render(){

    mWindow.clear();
    mWindow.draw(sPlayer);
    mWindow.draw(sRock);
    mWindow.display();
}
