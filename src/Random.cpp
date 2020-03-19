#include "Random.h"

#include <cstdlib>
#include <ctime>
#include <cassert>

template <class RAND>
Random<RAND>::Random(){
	srand(time(0));
}

template <class RAND>
RAND Random<RAND>::random(const RAND & min, const RAND & max){
    assert(min < max);
    return (rand()%(max-min+1))+min;
}
