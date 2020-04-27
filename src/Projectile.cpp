#include "Projectile.h"

Projectile::Projectile(const float entityX, const float entityY, const unsigned o, const unsigned type, const float speed, const unsigned collision) :
        positionProjectile(new Position<float>(entityX,entityY)), //puts bullet at the entity position
        nbCollision(0),
        speedProjectile(speed),
        entityType(static_cast<EntityType>(type)),
        orientation(static_cast<Orientation>(o)),
        collisionNb(collision){}

Projectile::~Projectile(){
	if (positionProjectile)
		delete positionProjectile;
	positionProjectile = nullptr;
}

void Projectile::update(){ //updates the position according to the orientation
    switch(orientation){
        case 0:
            positionProjectile->move(0, -0.1f*speedProjectile);
            break;
        case 1:
            positionProjectile->move(0.1f*speedProjectile, 0);
            break;
        case 2:
            positionProjectile->move(0, 0.1f*speedProjectile);
            break;
        case 3:
            positionProjectile->move(-0.1f*speedProjectile, 0);
            break;
    }
}

void Projectile::setCollisionNb(const unsigned nb){
    collisionNb = nb;
}

unsigned Projectile::getCollisionNb() const {
    return collisionNb;
}

unsigned Projectile::getProjectilePosition(bool xORy) const{
    return positionProjectile->getPosition(xORy);
}

void Projectile::collision(){
    //~Projectile(); ??????
	if (positionProjectile)
		delete positionProjectile;
    positionProjectile = nullptr;
    //check ennemy position and delete ennemy because collision with him
}

void Projectile::runsIntoWall(){
	if (positionProjectile){
		unsigned temp = getCollisionNb();
		if(temp > 1){
			setCollisionNb(temp-1);
		}
		else{//projectile has reached maximum collision number possible
			setCollisionNb(0);
			delete positionProjectile;
		}
	}
}

unsigned Projectile::getSpeedProjectile() const{
    return speedProjectile;
}

unsigned Projectile::getProjectileType() const{
    return entityType;
}

unsigned Projectile::getProjectileOrientation() const{
    return orientation;
}

void Projectile::displayProjectile() {
    std::cout << "X : " << getProjectilePosition(true) << " and Y : " << getProjectilePosition(false) << std::endl;
    std::cout<< "NB collisions          : " << getCollisionNb() << std::endl;
    std::cout<< "Projectile type        : " << entityType << std::endl;
    std::cout<< "Projectile orientation : " << orientation << std::endl;
    std::cout<<std::endl;
}
