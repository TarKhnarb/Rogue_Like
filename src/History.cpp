#include "History.h"

History::History() {
    Deroulement_du_jeu = Liste ();
    allQuests = ListQuests();
}

void History::ajouteAction(param1, param2 ...) {
    Action* p = Action(param1, param2 ...);
    Deroulement_du_jeu.ajouterEnTete(p);
    allQuests->upgrade(p);
}