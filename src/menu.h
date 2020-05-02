#ifndef MENU_MENU_H
#define MENU_MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>



class menu{
public :
    /**
     * @brief constructor
     */
    menu();
    /**
     * @brief used to load correct images and create rectangleShape for menu
     */
     void menuGame();
    /**
     * @brief resize window according to user imput
     */
    void displayMusicOption();
     /**
      * @brief display rules too player
      */
     void displayRule();
    /**
     * @brief check if mouse(first 2 parameters(X,y) is in boundaries of a rect given its size and position(last 4)
     * @param[in] mx : mouse X
     * @param[in] my : mouse y
     * @param[in] px : box position x
     * @param[in] py : box position y
     * @param[in] sx : box size x
     * @param[in] sy : box size y
     * @return true if in boundary, false if not
     */
    bool checkBound(const int,const int,const float,const float,const float,const float);
    /**
     * @brief takes a rectangleShape check if mouse (X,Y) which is the vector2i clicks in correct position, change current menu accordingly
     * @param[in] a vector composed of x,y of a mouse click
     * @param[in] a rectangleShape
     * @param[in] a unsigned char which is used when change current menu variable
     * @return true if inside bounds, false if not
     */
    bool checkPos(sf::RectangleShape,sf::Vector2i,unsigned char);

    /**
     * @brief takes a rectangleShpae check if mouse (X,Y) which is the vector2i clicks in correct position
     * @param[in] a rectangleShape
     * @param[in] a vector composed of x,y of a mouse click
     * @return true if inside bounds, false if not
     */
    bool checkPos(sf::RectangleShape,sf::Vector2i);//other things

    /**
     * @brief used to load mainMap appropriate textures/rectangleShape
     */
    void mainMap();
    /**
     * @brief move map instead of player so player sprite stays always in the middle
     */
    void move();

    /**
     * @brief load music file, start playing music
     */
    void musicFCT();
    /**
     * @brief check is variable sound if (true,false), starts,pause music accrodingly
     */
    void musicCheck();

    /**
     * @brief load textures according to path, given it's wanted size, and name of RectangleShape and Texture
     * @param[in] name: rectangleShape to load texture on
     * @param[in] name_: texture to load texture on
     * @param[in] X: size of rectangleShape on x
     * @param[in] Y: size of rectangleShape on y
     * @param[in] path : path of the texture to load
     */
    void loadTexture(sf::RectangleShape &,sf::Texture &, unsigned, unsigned, std::string);

protected :
    sf::RenderWindow mWindow;
    sf::Event event;
    //////////////////////////////////////
    unsigned char currentMenu;//0: main-menu//1: menu-map//2: option menu//3: rule menu
    std::string name="Aspen game";//name of game window
    std::string musicText="Do you want some music ?\n\n YES             or             NO ";

    /////////////Rectangle Shape
    unsigned X,Y;//window size
    sf::RectangleShape rectangleBack;
    sf::RectangleShape rectangleStart;
    sf::RectangleShape rectangleOption;
    sf::RectangleShape rectangleRule;
    sf::RectangleShape rectangleBackRule;
    sf::RectangleShape rectangleBackOption;
    sf::RectangleShape rectangleBackResize;
    sf::RectangleShape rectanglePosNeg[2];
    sf::RectangleShape rectangleMainMap;

    ////////////texture
    sf::Texture ruleTexture;
    sf::Texture backTexture;
    sf::Texture startTexture;
    sf::Texture resizeTexture;
    sf::Texture optionTexture;
    sf::Texture texturePosNeg[2];
    sf::Texture backgroundTexture;
    sf::Texture mainMapTexture;
    sf::Texture ruleBackgroundTexture;

    /////////// Music text
    sf::Font font;
    sf::Text text;
    /////////// MUSIC
    sf::Music music;
    bool sound;

};

#endif //MENU_MENU_H

