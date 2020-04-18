#include "Collision.h"

Collision::Collision(sf::RectangleShape &body):
        body(body){

}

Collision::~Collision(){}

void  Collision::Move(float dx, float dy){
    body.move(dx, dy);
}

bool Collision::CheckCollision(Collision &other, float push){

    sf::Vector2f otherPosition = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f thisPosition = other.getPosition();
    sf::Vector2f thisHalfSize = other.getHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if(intersectX < 0.0f && intersectY < 0.0f){
        push = std::min(std::max(push, 0.0f), 1.0f);

        if(intersectX > intersectY){
            if(deltaX > 0.0f){
                Move(intersectX * (1.0f - push), 0.0f);
                other.Move(-intersectX * push, 0.0f);
            }
            else{
                Move(-intersectX * (1.0f - push), 0.0f);
                other.Move(intersectX * push, 0.0f);
            }
        }
        else{
            if(deltaY > 0.0f){
                Move(0.0f, intersectY * (1.0f - push));
                other.Move(0.0f, -intersectY * push);
            }
            else{
                Move(0.0f, -intersectY * (1.0f - push));
                other.Move(0.0f, intersectY * push);
            }
        }
        return true;
    }

    return false;
}

sf::Vector2f Collision::getPosition(){
    return body.getPosition() + getHalfSize();
}
sf::Vector2f Collision::getHalfSize(){
    return body.getSize()/2.0f;
}