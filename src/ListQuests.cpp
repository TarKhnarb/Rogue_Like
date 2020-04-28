/*
#include "ListQuests.h"

ListQuests::ListQuests() {
    unsigned i = 1;
    while(i != idMaxQuest)
    {
        Mission* m = new Mission(i);
        Quests.push_back(m);
    }
}

ListQuests::~ListQuests() {
    for(unsigned i = 0; i < idMaxQuest; i++)
    {
        if (Quests[i])
        {
            delete Quests[i];
            Quests[i] =  nullptr;
        }
    }
}

void findFirstActive() {
    unsigned i = 0;
    while(i != idMaxQuest){
       if(Quests[i]->getActive()) return i + 1;
       else i++;
    }
    if(i = idMaxQuest) return 0;
}

void upgrade(Action)
{

}

*/
