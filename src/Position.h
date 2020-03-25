#ifndef GAME_POSITION_H
#define GAME_POSITION_H

#include <cmath>

#include "Random.h"

template <typename POS>

class Position{
public :
	Position() = default;
    Position(const POS &, const POS &);

    Position(const POS &,
             const POS &,
             const POS &,
             const POS &);

    Position operator = (const Position &);
    bool operator == (const Position &);
    bool operator < (const Position &);
    Position move (const POS &, const POS &);

    POS getPosition(bool) const;
    void setPosition(const POS &, const POS &);

    //distance selon x OU y
    POS dist(const Position &, bool) const;
    //distance selon x ET y
    POS distance(const Position &) const;



private :
    POS x,y;
};

#endif //GAME_POSITION_H

template <class POS>
Position<POS>::Position(const POS & a, const POS & b) {
    x=a;
    y=b;
}

template <class POS>
Position<POS>::Position(const POS & minX,
                        const POS & minY,
                        const POS & maxX,
                        const POS & maxY) {
    assert(minX < maxX && minY < maxY);

    x=Random<POS>::random(minX,maxX);
    y=Random<POS>::random(minY,maxY);
}

template <class POS>
Position<POS> Position<POS>::operator = (const Position & a){
    x=a.x;
    y=a.y;
}

template <class POS>
bool Position<POS>::operator == (const Position & a){
    if(a.x == x && a.y == y)
        return true;
    else
        return false;
}

template <class POS>
bool Position<POS>::operator < (const Position & a){
    if(x < a.x && y < a.y)
        return true;
}

template <class POS>
Position<POS> Position<POS>::move(const POS & a, const POS & b){
    x+=a;
    y+=b;

    return Position<POS> (x, y);
}

template <class POS>
POS Position<POS>::getPosition(bool xORy) const {
    if(xORy)
        return x;
    else
        return y;
}

template <class POS>
void Position<POS>::setPosition(const POS & a, const POS & b) {
    x=a;
    y=b;
}

template <class POS>
POS Position<POS>::dist(const Position & a, bool xORy) const {
    if(xORy)
        return abs(x+-a.x);
    else
        return abs(y-a.y);
}


template <class POS>
POS Position<POS>::distance(const Position & a) const {
    POS Y = a.y-y;
    POS X = a.x-x;
    return sqrt((Y*Y)+(X*X));
}
