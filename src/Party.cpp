#include "Party.h"

Party::Party():
        mWindow(sf::VideoMode(640, 480), "Aspen's Adventure"),
        mTexture(),
        mPlayer(){

    if (!mTexture.loadFromFile("data/Textures/Aspen.png"))
        std::cout << "error sprite" << std::endl;

    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(320.f, 240.f);
}

Party::~Party() {
    for(auto &t : textures){
        delete t.second;
        t.second = nullptr;
    }
}

void Party::loadTextures(){ // load dans le constructeur
        // Entity
            //Aspen
    sf::Texture* texture(new sf::Texture ());
    texture->loadFromFile("data/Entity/AspenB.png");
    textures.emplace("AspenB", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenB1.png");
    textures.emplace("AspenB1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenB2.png");
    textures.emplace("AspenB2", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenF.png");
    textures.emplace("AspenF", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenF1.png");
    textures.emplace("AspenF1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenF2.png");
    textures.emplace("AspenF2", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenL.png");
    textures.emplace("AspenL", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenL1.png");
    textures.emplace("AspenL1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenL2.png");
    textures.emplace("AspenL2", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenL3.png");
    textures.emplace("AspenL3", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenR.png");
    textures.emplace("AspenR", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenR1.png");
    textures.emplace("AspenR1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenR2.png");
    textures.emplace("AspenR2", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Entity/AspenR3.png");
    textures.emplace("AspenR3", texture);

        // Room
            // Start/Boss
    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Start.png");
    textures.emplace("RoomStart", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Boss.png");
    textures.emplace("RoomBoss", texture);

            // 1 Door
    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room1E.png");
    textures.emplace("Room1E", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room1N.png");
    textures.emplace("Room1N", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room1S.png");
    textures.emplace("Room1S", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room1W.png");
    textures.emplace("Room1W", texture);

            // 2 Doors
    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room2NS1.png");
    textures.emplace("Room2NS1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room2NS2.png");
    textures.emplace("Room2NS2", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room2WE1.png");
    textures.emplace("Room2WE1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room2WE2.png");
    textures.emplace("Room2WE2", texture);

            // 3 Doors
    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room3ESW.png");
    textures.emplace("RoomESW", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room3NES.png");
    textures.emplace("Room3NES", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room3NEW.png");
    textures.emplace("Room3NEW", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room3NSW.png");
    textures.emplace("Room3NSW", texture);

            // 4 Doors
    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room4NESW1.png");
    textures.emplace("Room4NESW1", texture);

    texture = new sf::Texture();
    texture->loadFromFile("data/Room/Room4NESW2.png");
    textures.emplace("Room4NESW2", texture);
    /*
     * Là on charge toutes les textures et on les nommes (cf au dessus)
     */
}

sf::Texture& Party::getTexture(const std::string& nameText){ // récupere un etexture quand on en a besoin
    auto found = textures.find(nameText);
    if(found == textures.end())
        throw std::runtime_error ("Party::getTexture(const std::string&) - Aucune texture de ce nom " + nameText);

    return *found->second; // ( si pas * on retourne un pointeur de texture)
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
    if (mIsMovingUp)
        movement.y -= PlayerSpeed;

    if (mIsMovingDown)
        movement.y += PlayerSpeed;

    if (mIsMovingLeft)
        movement.x -= PlayerSpeed;

    if (mIsMovingRight)
        movement.x += PlayerSpeed;

    mPlayer.move(movement * deltaTime.asSeconds());
}

void Party::render(){

    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}
