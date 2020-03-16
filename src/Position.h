#ifndef GAME_POSITION_H
#define GAME_POSITION_H

#include "Random.h"

template <class POS>

class Position{
public :
    Position(const POS &, const POS &);

    Position(const POS &,
             const POS &,
             const POS &,
             const POS &);

     ~Position();
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
