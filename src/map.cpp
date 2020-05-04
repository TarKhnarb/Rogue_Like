#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "map.h"
#include <cmath>
#include <iostream>

map::map():
        posAspen(1364, 725),
        Aspen (posAspen.getPosition(true), posAspen.getPosition(false)){

    sf::RenderWindow mWindow(sf::VideoMode(X,Y),"map");

    view = sf::View({0.f, 0.f, float(mWindow.getSize().x), float(mWindow.getSize().y)});

    mWindow.setFramerateLimit(60);

    loadTextures();

    loadRectangleShape("map_menu");
    loadRectangleShape("Trader");
    loadRectangleShape("Witch");
    loadRectangleShape("Blacksmith");
    loadRectangleShape("Crafter");

    if (scroll.loadFromFile("data/Font/verdana.ttf")){ // charge le police d'écriture verdana
        objectsFont.loadFromFile("data/Font/verdana.ttf");
        statsFont.loadFromFile("data/Font/verdana.ttf");
    }
    else{
        throw std::runtime_error ("Failed to load data/Font/verdana.ttf");
    }

    npcCollider.setStyle(Style::Separated);

    loadAnimation();
    setInventoryItem();
    setAllRectangleShape();
}

map::~map(){
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

void map::run(){

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f / 30.f);
    std::cout << "1" << std::endl;

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
        }

        render();
    }
}

std::string map::returnCsvItem(std::istringstream & ss){
    std::string res;
    std::getline(ss,res,',');
    return res;
}

void map::loadTextures(){ // load dans le constructeur
    std::ifstream file;
    std::string filename = "data/TexturesMap.csv";
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

sf::Texture* map::getTexture(const std::string& nameText){ // récupere un etexture quand on en a besoin
    auto found = textures.find(nameText);
    if(found == textures.end())
        throw std::runtime_error ("Aucune texture de ce nom " + nameText);

    return found->second; // ( si pas * on retourne un pointeur de texture)
}

void map::loadRectangleShape(std::string name){
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

sf::RectangleShape map::getRectangleShape(const std::string& name){
    auto found = rectangleShapes.find(name);
    if(found == rectangleShapes.end())
        throw std::runtime_error ("Aucun rectangleShape de ce nom " + name);

    return *found->second;
}

void map::loadAnimation(){

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

void map::setMapRectangleShape(){
    rectBackMap.setSize(sf::Vector2f(2*X,2*Y));//load back map
    rectBackMap.setFillColor(sf::Color(148, 223, 231, 255));
    rectBackMap.setPosition({0.f, 0.f});

    rectMainMap.setSize(sf::Vector2f(X,Y));
    rectMainMap.setTexture(getTexture("map_menu"));
    rectMainMap.setPosition({640.f, 360.f});
}

void map::setNpcRectangleShape(){
    sf::RectangleShape bl({35.f, 35.f});
    bl.setTexture(getTexture("Blacksmith"));
    bl.setPosition({1077.f, 685.f});
    npcR.push_back(bl);

    sf::RectangleShape wi({35.f, 35.f});
    wi.setTexture(getTexture("Witch"));
    wi.setPosition({1632.f, 838.f});
    npcR.push_back(wi);

    sf::RectangleShape tr({35.f, 35.f});
    tr.setTexture(getTexture("Trader"));
    tr.setPosition({843.f, 807.f});
    npcR.push_back(tr);

    sf::RectangleShape cr({35.f, 35.f});
    cr.setTexture(getTexture("Crafter"));
    cr.setPosition({1632.f, 838.f});
    npcR.push_back(cr);

    npcCollider.pushBodies(npcR.begin(), npcR.end());
}

void map::setWallRectangleShape(){
    for(unsigned i = 0; i < 25; ++i){
        sf::Vector2f vect(arch.wallMap[i][2], arch.wallMap[i][3]);
        sf::RectangleShape rect(vect); // set de la taille du rectangle
        rect.setPosition(arch.wallMap[i][0], arch.wallMap[i][1]); // on set la position du rectangle
        wall.push_back(rect);
    }

    wallsCollider.pushBodies(wall.begin(), wall.end());
}

void map::setAllRectangleShape(){
    setMapRectangleShape();
    setNpcRectangleShape();
    setWallRectangleShape();
}

void map::setInventoryStats(){

    textStats.resize(0);

    sf::Text txtStat;
    txtStat.setFont(statsFont);
    txtStat.setCharacterSize(10);
    txtStat.setFillColor(sf::Color::White);
    txtStat.setOutlineColor(sf::Color::Black);
    txtStat.setOutlineThickness(1.f);

    txtStat.setString("Max Life :   "+ std::to_string(Aspen.getMaxLife()));
    txtStat.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.statInventory[0][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.statInventory[0][1]);
    textStats.push_back(txtStat);

    txtStat.setString("Attack :   "+ std::to_string(Aspen.getAttack()));
    txtStat.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.statInventory[0][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.statInventory[0][1] + 25.f);
    textStats.push_back(txtStat);

    txtStat.setString("AttackSpeed :   "+ std::to_string(Aspen.getAttackSpeed()));
    txtStat.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.statInventory[0][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.statInventory[0][1] + 50.f);
    textStats.push_back(txtStat);

    txtStat.setString("Defence :   "+ std::to_string(Aspen.getDefence()));
    txtStat.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.statInventory[1][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.statInventory[1][1]);
    textStats.push_back(txtStat);

    txtStat.setString("Speed :   "+ std::to_string(Aspen.getSpeed()));
    txtStat.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.statInventory[1][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.statInventory[1][1] + 25.f);
    textStats.push_back(txtStat);

    txtStat.setString("Money :   "+ std::to_string(Aspen.getMoney()));
    txtStat.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.statInventory[1][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.statInventory[1][1] + 50.f);
    textStats.push_back(txtStat);
}

sf::Color map::setItemLvl(unsigned id){
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

void map::setInventoryItem(){

    viewAspen.setSize({60.f, 120.f});
    viewAspen.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.inventoryAspen[0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.inventoryAspen[1]);
    sf::Texture *textu = getTexture("AspenFront");
    textu->setSmooth(true);
    viewAspen.setTexture(textu);
    viewAspen.setTextureRect(sf::IntRect(0, 0, 40, 80));

    playerInventory.setSize({480.f, 280.f});
    playerInventory.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.playerInventory[0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.playerInventory[1]);
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
            item.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[i][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[i][1]);

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
                txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[i][0] + 48.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[i][1] + 48.f);

                objectsNumber.emplace(i, txt);
            }
        }
        else{
            item.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[i][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[i][1]);
            item.setTexture(*getTexture("Nothing"));
            bagItem.emplace(i, item);
        }
    }

    for (unsigned i = 0; i < playerStuffSize; ++i){
        sf::Sprite item;
        const Object* object = Aspen.getInventoryStuff(i);

        if(object){
            item.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemStuff[i][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemStuff[i][1]);

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
            item.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemStuff[i][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemStuff[i][1]);
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
/*
void map::setChestItem(){
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
}*/

void map::setScrollingMenu(){

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
                txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemStuff[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemStuff[inventoryIndex][1]);
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
                    txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[inventoryIndex][1]);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    txt.setString("Trash");
                    txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[inventoryIndex][1] + 15.f);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    if(chestOpen){
                        txt.setString("Add to chest");
                        txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[inventoryIndex][1] + 30.f);
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
                    txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[inventoryIndex][1]);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    txt.setString("Move");
                    txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[inventoryIndex][1] + 15.f);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    txt.setString("Trash");
                    txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[inventoryIndex][1] + 30.f);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    if(chestOpen){
                        txt.setString("Add to chest");
                        txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[inventoryIndex][1] + 45.f);
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
                    txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[inventoryIndex][1]);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    txt.setString("Move");
                    txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[inventoryIndex][1] + 15.f);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    txt.setString("Trash");
                    txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[inventoryIndex][1] + 30.f);
                    textScrolling.push_back(txt);

                    scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                    bounds = txt.getGlobalBounds();
                    scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                    rectangleShapeScrolling.push_back(scrollMenu);

                    if(chestOpen){
                        txt.setString("Add to chest");
                        txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[inventoryIndex][1] + 45.f);
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

       /* case 3: { // ajouter a l'inventaire(enlever du coffre) seulement s'il y a un object, sinon fermer le scrollingMenu

            if (donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getChest()->getItem(inventoryIndex)) {
                scrollingValue = 1;
                txt.setString("Add to inventory");
                txt.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemChest[inventoryIndex][0] + 52.f, (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemChest[inventoryIndex][1]);
                textScrolling.push_back(txt);

                scrollMenu.setPosition(txt.getPosition().x - 2.f, txt.getPosition().y);
                bounds = txt.getGlobalBounds();
                scrollMenu.setSize({bounds.width + 4.f, bounds.height * 1.8f});
                rectangleShapeScrolling.push_back(scrollMenu);
            } else
                scrollingMenuOpen = false;
            break;
        }*/

        default:
            break;
    }
}

void map::updateScrollingMenu(){

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
                   /* else if(action == std::string("Add to inventory")){ // on ajoute l'objet du coffre a l'inventaire

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
                    }*/
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

void map::updateMoveObject(){
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

    moveCursor.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[moveObjectIndex][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[moveObjectIndex][1]);
}

void map::updateInventory(){
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
                   /* else if (inventoryValue == 3){ // dans le coffre
                        if (inventoryIndex < chestSize - 1)
                            ++inventoryIndex;
                    }*/
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
            sInventoryCursor.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemStuff[inventoryIndex][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemStuff[inventoryIndex][1]);
            break;

        case 2:
            sInventoryCursor.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemBag[inventoryIndex][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemBag[inventoryIndex][1]);
            break;

        case 3:
            sInventoryCursor.setPosition((posAspen.getPosition(true) - (mWindow.getSize().x/2.f)) + arch.itemChest[inventoryIndex][0], (posAspen.getPosition(false) - (mWindow.getSize().y/2.f)) + arch.itemChest[inventoryIndex][1]);
            break;

        default:
            break;
    }

}
/*
void map::drawChestInventory(){
    Chest *chest = donjon.getRoom(posDonjon.getPosition(true), posDonjon.getPosition(false))->getChest();

    if(chest && chestOpen){
        mWindow.draw(chestInventory);

        for(auto &c : chestItem)
            mWindow.draw(c.second);

        for(auto &n : chestObjectNumber)
            mWindow.draw(n.second);

        mWindow.draw(sInventoryCursor);
    }
}*/

void map::drawPlayerInventory(){ // 1: stuff, 2: bag, 3: chest
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

void map::updateException(){
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
            exceptionState = false;
        }
    }
}

void map::drawException(){
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

void map::entityCollision(){

    sf::RectangleShape sPlayerCol ({(aspenAnimated.getLocalBounds()).width, (aspenAnimated.getLocalBounds()).height / 2.f});
    sPlayerCol.setOrigin({0.f, sPlayerCol.getSize().y});
    sPlayerCol.setPosition(aspenAnimated.getPosition().x, aspenAnimated.getPosition().y + (aspenAnimated.getLocalBounds()).height);
    sPlayerCol.move(0.f, (aspenAnimated.getLocalBounds()).height / 6.f);

    sf::Vector2f colDirection;
    sf::Vector2f posBegin = sPlayerCol.getPosition();

    Collider playerCol (sPlayerCol);

        // Walls
    playerCol.checkCollision(wallsCollider, colDirection, 0.f);

    std::vector<std::pair<std::size_t, std::size_t>> npcCollisions;

    if(playerCol.checkCollision(npcCollider, npcCollisions, 0.f)){
        for(auto c : npcCollisions){
            switch(c.second){
                case 0:
                    std::cout << "Blacksmith" << std::endl;
                    break;

                case 1:
                    std::cout << "Witch" << std::endl;
                    break;

                case 2:
                    std::cout << "Trader" << std::endl;
                    break;

                case 3:
                    std::cout << "Crafter" << std::endl;
                    break;

                default:
                    break;
            }
        }
    }

    sf::Vector2f posEnd = sPlayerCol.getPosition();

    posAspen.move(posEnd.x - posBegin.x, posEnd.y - posBegin.y);
    aspenAnimated.setPosition(posAspen.getPosition(true), posAspen.getPosition(false));
}

void map::processEvents(){

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

void map::handlePlayerInput(sf::Keyboard::Key key, bool isPressed){

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

void map::update(sf::Time deltaTime){

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

    aspenAnimated.play(*currentAnimation);
    posAspen.move(movement.x * deltaTime.asSeconds(), movement.y * deltaTime.asSeconds());
    aspenAnimated.setPosition(posAspen.getPosition(true), posAspen.getPosition(false));

    if (noKeyWasPressed){
        aspenAnimated.stop();
    }
    noKeyWasPressed = true;

    aspenAnimated.update(deltaTime);

    entityCollision();

    view.setCenter(posAspen.getPosition(true), posAspen.getPosition(false));
}

void map::render(){

    mWindow.setView(view);

    mWindow.clear();

    mWindow.draw(rectBackMap);
    mWindow.draw(rectMainMap);

    for(auto &n : npcR)
        mWindow.draw(n);

    mWindow.draw(aspenAnimated);

    if(inventoryOpen) {
        drawPlayerInventory();
    }

    if(exceptionState){
        drawException();
    }

    mWindow.display();
}
