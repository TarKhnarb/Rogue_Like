#include "ListQuests.h"

ListQuests::ListQuests(){
    for(unsigned i = 1; i < idMaxQuest+1; i++)
    {
        Quests.push_back(new Mission(i));
    }
}

ListQuests::~ListQuests(){
    for(unsigned i = 0; i < Quests.size(); ++i){
        if (Quests[i])
            delete Quests[i];
        Quests[i] = nullptr;
    }
}

void ListQuests::update(Entity* hero){
    for(unsigned i = 0; i < Quests.size(); i++)
    {
        if(i<3){
            if(!Quests[i]->getComplete())
            {
                Quests[i]->update(hero,*Quests[i],*Quests[i]);
            }
        }
        else
        if(!Quests[i]->getComplete())
        {
            Quests[i]->update(hero,*Quests[i-1],*Quests[i-2]);
        }

    }
}

void ListQuests::areComplete() const {
    for(unsigned i = 0; i < Quests.size(); i++)
    {
        Quests[i]->isComplete();
    }
}

