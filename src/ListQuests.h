#ifndef _LISTQUESTS_H
#define _LISTQUESTS_H

#include "Mission.h"

const unsigned idMaxQuest = 5;

class ListQuests {
public:
    ListQuests();

    ~ListQuests();

    void findFirstActive();

    void upgrade(Action);

private:
    std::vector<Mission*> Quests;
};

#endif //LISTQUESTS_H