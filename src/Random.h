#ifndef GAME_RANDOM_H
#define GAME_RANDOM_H

#include <cstdlib>
#include <ctime>
#include <cassert>

template <class RAND>

class Random{
public :
	Random();
	static RAND random(const RAND &, const RAND &);
};

#endif //GAME_RANDOM_H

//verifier le rand car parfois pas dans les bornes max et min
