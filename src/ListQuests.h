#ifndef _LISTQUESTS_H
#define _LISTQUESTS_H

#include "Mission.h"
#include "Entity.h"

const unsigned idMaxQuest = 9;

class ListQuests {
public:
    ListQuests();

    ~ListQuests();

    void update(Entity*);

    void areComplete() const;

private:
    std::vector<Mission*> Quests;
};

#endif //LISTQUESTS_H