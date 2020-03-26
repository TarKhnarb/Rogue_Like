#include "Donjon.h"

Donjon::Donjon(unsigned stageNumb){

    stage = stageNumb;
    currentStage = new Stage();
}

void Donjon::DonjonGame() {
    currentStage->generate(stage);
}
