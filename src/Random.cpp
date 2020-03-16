#include "Random.h"

#include <cstdlib>
#include <time.h>
#include <assert.h>

template <class RAND>
RAND Random<RAND>::random(const RAND & min, const RAND & max){
    assert(min < max);
    return (rand()%(max-min+1))+min;
}