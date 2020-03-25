#include "Stage.h"

class Donjon{

public:

    Donjon();
  //  Donjon(unsigned); // Pour commencer avec un seed précis

    unsigned getStage() const;

    void DonjonGame();

private:

    unsigned stage;
    unsigned seed;

    Stage* currentStage;
};