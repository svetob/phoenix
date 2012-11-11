#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H

#include <set>
#include <map>

#include "entity.h"
#include "component.h"

/* TODO:
   Improvement:
   - Instead of storing entities by the components they posess...
   - ...track a set of pre-defined component combinations.
   - Each System registers which combinations to track.
   This will reduce getByComponents from O(n) to roughly O(1).
   Then all operations in this manager will be  O(1) or O(log n). */

class EntityManager
{
private:
    std::set<Entity*>* entAll;
    std::map<COMP_TYPE, std::set<Entity*>*>* entByComp;

public:
    EntityManager();
    ~EntityManager();

    // Entity insertion and removal
    void insert(Entity* e);
    void remove(Entity* e);

    // Entity aquiral
    inline const std::set<Entity*>* getAll() { return entAll; };
    const std::set<Entity*>* getByComponent(COMP_TYPE t);
    std::set<Entity*>* getByComponents(std::vector<COMP_TYPE>* cts);
};

#endif
