#ifndef GAME_PROJECTILE_H
#define GAME_PROJECTILE_H

#include <iostream>

#include "Position.h"

class Projectile {
public:

    enum EntityType{
        player, // 0
        monster, // 1
    };

    enum Orientation{
        north, //0
        south, //1
        east , //2
        west ,//3
    };

    /**
     * @brief constructor
     * @param[in] entityX : position X axis of entity when fires
     * @param[in] entityY : position Y axis of entity when fires
     * @param[in] o : orientation of projectile which depends of orientation of entity when fired
     * @param[in] type : type of the person who launched the projectile (0 if player, 1 monster)
     * */
    Projectile(const unsigned, const unsigned, const unsigned &,const unsigned &);

    /**
     *  @brief destructor
     */
    ~Projectile();

    /**
     * @brief sets number of collision for a projectile
     * @param[in] nb : number of collision for a projectile
     */
    void setCollisionNb(const unsigned &);

    /**
     * @return nb of collision left for an object
     */
     unsigned getCollisionNb() const;

    /**
     * @brief what to do in case of collisions
     */
    void collision();

    /**
     * @brief update position of projectile according to orientation
     */
    void update();

    /**
     * @brief if projectile runs into wall then delete
     */
     void runsIntoWall();

    /**
     * @brief get position of projectile
     * @param[in] xORy : a bool to choose between X position or Y position
     * @return X value if bool is true, Y if false
     */
    unsigned getProjectilePosition(bool) const;

    /**
     * @brief get speed of projectile
     */
     unsigned getSpeedProjectile() const;

     /**
     * @brief get type of projectile
     * @return an unsigned int related to the enum
     */
     unsigned getProjectileType() const;

    /**
    * @brief get orientation of projectile
    * @return an unsigned int related to the enum
    */
    unsigned getProjectileOrientation() const;
    
    /**
     * @brief display stats of projectile //good for debug
     */
    void displayProjectile();

private:
    Position<unsigned> * positionProjectile;
    unsigned nbCollision;
    unsigned speedProjectile;
    EntityType entityType; // O : player, 1 : monster
    Orientation orientation; //0 = North, 1 = East, 2 = South, 3 = West
    unsigned collisionNb;
};


#endif //PROJECTILE_H
