#ifndef _HISTORY_H
#define _HISTORY_H

#include "Action.h"
#include "ListQuests.h"

class History {
public:
    History();

    void ajouteActionDansHitorique(param1, param2 ...);

private:
    Liste Deroulement_du_jeu;
    ListQuests* allQuests;
};

#endif //HISTORY_H