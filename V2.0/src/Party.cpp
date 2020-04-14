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
    sf::Texture* texture(new sf::Texture ());
    texture->loadFromFile("data/Textures/Aspen.png");
    textures.emplace("Aspen", texture);

    texture = new sf::Texture();
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

    if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;

    if (key == sf::Keyboard::Q)
        mIsMovingLeft = isPressed;

    if (key == sf::Keyboard::D)
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
