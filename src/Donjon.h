#include "Stage.h"

const unsigned stageNumber = 6;

class Donjon{

public:

    Donjon(unsigned);
  //  Donjon(unsigned); // Pour commencer avec un seed précis

    unsigned getCurrentStage(unsigned) const;

    void DonjonGame();

private:

    unsigned stage;
    unsigned seed;
    Stage *currentStage;
};