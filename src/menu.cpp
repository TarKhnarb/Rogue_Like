#include "menu.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

menu::menu(){
    X=800;
    Y=800;
    sf::RenderWindow mWindow(sf::VideoMode(X,Y),name);
    mWindow.setFramerateLimit(60);
    font.loadFromFile("data/Font/font.ttf");
    currentMenu = 0;
    menuGame();
    displayRule();
    displayMusicOption();
    mainMap();
    musicFCT();

    while (mWindow.isOpen()){
        while (mWindow.pollEvent(event)){
            switch(currentMenu){
                case 0://main-menu
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        sf::Vector2i globalPosition = sf::Mouse::getPosition(mWindow);
                        if(checkPos(rectangleStart,globalPosition,1)){}
                        if(checkPos(rectangleOption,globalPosition,2)){}
                        if(checkPos(rectangleRule, globalPosition, 3)){}
                    }
                    break;
                case 1://menu-map
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        sf::Vector2i globalPosition = sf::Mouse::getPosition(mWindow);
                        if(checkPos(rectangleBackOption,globalPosition,0)){}
                    }
                    move();
                    //call map
                    break;
                case 2://option-menu
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        sf::Vector2i globalPosition = sf::Mouse::getPosition(mWindow);
                        if(checkPos(rectangleBackOption,globalPosition,0)){}

                        if(checkPos(rectanglePosNeg[0],globalPosition)){
                            sound = true;
                            musicCheck();
                        }
                        if(checkPos(rectanglePosNeg[1],globalPosition)){
                            sound = false;
                            musicCheck();
                        }
                    }
                    break;
                case 3://rule-map
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        sf::Vector2i globalPosition = sf::Mouse::getPosition(mWindow);
                        if(checkPos(rectangleBackOption,globalPosition,0)){}
                    }
                    break;
                default:
                    break;
            }
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                mWindow.close();
        }
        //end event loop

        //draw switch
        mWindow.clear();
        switch(currentMenu){
            case 0:
                mWindow.draw(rectangleBack);
                mWindow.draw(rectangleStart);
                mWindow.draw(rectangleOption);
                mWindow.draw(rectangleRule);
                break;
            case 1:
              //  mWindow.draw(rectangleMainMap);
              //  mWindow.draw(rectangleBackOption);
              //  break;
              //call map
            case 2:
                mWindow.draw(rectangleBackResize);
                mWindow.draw(rectangleBackOption);
                mWindow.draw(text);
                mWindow.draw(rectanglePosNeg[0]);
                mWindow.draw(rectanglePosNeg[1]);
                break;
            case 3:
                mWindow.draw(rectangleBackRule);
                mWindow.draw(rectangleBackOption);
                break;
            default:
                break;
        }
        //end draw switch
        mWindow.display();
    }
}

void menu::musicFCT(){
    sound = true;
    music.openFromFile("data/Audio/sound_music.wav");
    music.play();
    music.setLoop(true);
}

void menu::musicCheck(){
    if(sound)
        music.play();
    else
        music.stop();
}

bool menu::checkBound(const int mx,const int my,const float px,const float py,const float sx,const float sy){
    if(mx > px && my > py){          //check min
        if(mx < px+sx && my < py+sy) //check max
            return true;
        else
            return false;
    }
    else
        return false;
}

bool menu::checkPos(sf::RectangleShape r,sf::Vector2i g,unsigned char n) {
    sf::Vector2f tempS = r.getSize();
    sf::Vector2f tempP = r.getPosition();
    if (checkBound(g.x, g.y, tempP.x, tempP.y, tempS.x / 2, tempS.y / 2)){
        currentMenu = n;
        return true;
    }
    else
        return false;
}

bool menu::checkPos(sf::RectangleShape r,sf::Vector2i g) {
    sf::Vector2f tempS = r.getSize();
    sf::Vector2f tempP = r.getPosition();
    if (checkBound(g.x, g.y, tempP.x, tempP.y, tempS.x / 2, tempS.y / 2))
        return true;
    else
        return false;
}

void menu::loadTexture(sf::RectangleShape & name, sf::Texture & name_,const unsigned X,const unsigned Y,const std::string path){
    name.setSize(sf::Vector2f(X,Y));
    name_.loadFromFile(path);
    name.setTexture(&name_);
}



void menu::menuGame(){
    loadTexture(rectangleBack,backgroundTexture,X,Y,"data/Textures/Menu/menu_background.png");

    loadTexture(rectangleStart,startTexture,300,150,"data/Textures/Menu/start.png");
    rectangleStart.scale(0.5,0.5);
    rectangleStart.setPosition(3.8*(X/10),2.5*(Y/10));

    loadTexture(rectangleOption,optionTexture,300,150,"data/Textures/Menu/option.png");
    rectangleOption.scale(0.5,0.5);
    rectangleOption.setPosition(3.8*(X/10),4.5*(Y/10));

    loadTexture(rectangleRule,ruleTexture,300,150,"data/Textures/Menu/rule.png");
    rectangleRule.scale(0.5,0.5);
    rectangleRule.setPosition(3.8*(X/10),6.5*(Y/10));
}

void menu::displayRule(){
    loadTexture(rectangleBackRule,ruleBackgroundTexture,X,Y,"data/Textures/Menu/backgroundRule.png");

    loadTexture(rectangleBackOption,backTexture,100,200,"data/Textures/Menu/back_logo.png");
    rectangleBackOption.scale(0.3,0.2);
    rectangleBackOption.setPosition((X/10),(Y/10));
}

void menu::displayMusicOption(){
    loadTexture(rectangleBackResize,resizeTexture,X,Y,"data/Textures/Menu/backgroundOption.png");

    //fonts+text
    text.setFont(font);
    text.setString(musicText);
    text.setCharacterSize(50);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(1.5*(X/10),2*(Y/10));
    text.setFillColor(sf::Color::White);

    for(unsigned char i=0;i<2;++i){
        if(i==0) {
            loadTexture(rectanglePosNeg[i],texturePosNeg[i],X,Y,"data/Textures/Menu/yes.png");
            rectanglePosNeg[i].setPosition(2*(X / 10), 5 * (Y / 10));
            rectanglePosNeg[i].scale(0.2,0.2);
        }else{
            loadTexture(rectanglePosNeg[i],texturePosNeg[i],X,Y,"data/Textures/Menu/red.png");
            rectanglePosNeg[i].setPosition(6*(X / 10), 5 * (Y / 10));
            rectanglePosNeg[i].scale(0.2,0.2);
        }
    }
}

void menu::mainMap(){
    loadTexture(rectangleMainMap,mainMapTexture,2*X,2*Y,"data/Textures/Menu/main_map.png");
    rectangleMainMap.setPosition(0*(X/10),0*(Y/10));
    rectangleMainMap.setOrigin(4*(X/10),4*(Y/10));
}

void menu::move(){
    float x=0,y=0;
   //normalement eazy pr les dimensions de la map(a voir comment faire pr la nouvelle map)
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q){
        if(rectangleMainMap.getPosition().x<int(X/2))
            x=10;
    }
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D){
        if(rectangleMainMap.getPosition().x>-int(X/2))
            x=-10;
    }
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z){
        if(rectangleMainMap.getPosition().y<int(Y/2))
            y=10;
    }
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S){
        if(rectangleMainMap.getPosition().y>-int(Y/2))
            y=-10;
    }
    rectangleMainMap.move(x,y);
}


