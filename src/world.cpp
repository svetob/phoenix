#include "world.h"


void World::runOnce()
{
    std::vector<ISystem*>::iterator it;
    
    std::vector<COMP_TYPE>* cts;
    ISystem* s;

    for (it = systems.begin(); it != systems.end(); ++it)
    {
        s = *it;
        cts = s->getRequiredComponents();
        if (cts->size() == 0)
        {
            s->update(getEntities());
        }
        if (cts->size() == 1)
        {
            s->update(getEntities(cts[0][0]));
        }
        else if (cts->size() >= 2)
        {
            std::set<Entity*>* entities = getEntities(cts);
            s->update(entities);
            delete entities;
        }
    }
}
