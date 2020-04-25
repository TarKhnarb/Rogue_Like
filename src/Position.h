#ifndef GAME_POSITION_H
#define GAME_POSITION_H

#include <cmath>

template <typename POS>

class Position{

public :
    /**
     * @brief constructor by default
     */
	Position() = default;
    
    /**
     * @brief constructor which inits what has to be init at value x and y on x and y axis respectively
     * @param[in] x: position on x axis
     * @param[in] y: position on y axis
     */
    Position(const POS &, const POS &);

    /**
     * @brief inits what has be be init at a random position between minX && maxX and minY && maxY
     * @param[in] minX : minimum value for x axis
     * @param[in] minY : minimum value for y axis
     * @param[in] maxX : maximum value for x axis
     * @param[in] maxY : maximum value for y axis
     */
   /* Position(const POS &,
             const POS &,
             const POS &,
             const POS &);
    */

    /**
      * @brief affects x and y value to another Position
      * @param[in] a : a position
      * @return a new position with x and y value from the parameter position
      */
    Position operator = (const Position &);
    
    /**
     * @brief check if both position are equal on both x and y axis
     * @param[in] a : position
     * @return a bool at true if yes, and no if not
     */
    bool operator == (const Position &);
    
    /**
     * @brief checks if one position is lower than another on in parameter
     * @param[in] a : a position
     * @return a bool at true if lower, false if not
     */
    bool operator < (const Position &);
    
    /**
     * @brief changes x and y value of the position
     * @param[in] a : the value of what had to be added to the x axis
     * @param[in] b : the value of what had to be added to the y axis
     * @return the new position
     */
    Position move (const POS &, const POS &);

    /**
     * @brief gets the position on x OR y axis
     * @param[in] xORy : true >> gets x axis value, false >> gets y axis value
     * @return the value
     */
    POS getPosition(bool) const;
    
    /**
     * @brief sets the new position
     * @param[in] a : x axis value
     * @param[in] b : y axis value
     */
    void setPosition(const POS &, const POS &);

    /**
     * @brief gets the absolute distance between two positions on x OR y axis
     * @param[in] a : a position
     * @param[in] xORy : true >> gets the x axis distance between 2 positions >> y if false
     * @return the absolute distance
     */
    POS dist(const Position &, bool) const;
    
     /**
     * @brief returns the absolute distance according to x AND y axis
     * @param[in] a : a position
     * @return an absolute distance
     */
    POS distance(const Position &) const;

private :
    POS x,y;
};

template <class POS>
Position<POS>::Position(const POS & a, const POS & b) {
    x=a;
    y=b;
}

//not currently uselful
/*
template <class POS>
Position<POS>::Position(const POS & minX,
                        const POS & minY,
                        const POS & maxX,
                        const POS & maxY) {
    assert(minX < maxX && minY < maxY);

    x=Random<POS>::random(minX,maxX);
    y=Random<POS>::random(minY,maxY);
}*/

template <class POS>
Position<POS> Position<POS>::operator = (const Position & a){
    x=a.x;
    y=a.y;
    return Position<POS> (x, y);
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
    //pythagorean distance (does not take into account obstacles or not)
    //just a straight line bewteen 2 points
    POS Y = a.y-y;
    POS X = a.x-x;
    return sqrt((Y*Y)+(X*X));
}

#endif //POSITION_H