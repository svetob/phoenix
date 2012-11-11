#ifndef _WORLD_H
#define _WORLD_H

#include "entity.h"
#include "entityManager.h"
#include "system.h"

class World
{
private:
    /* We will likely need to add an EntityManager for performance reasons
       This could be a hashmap using Entity name as key? */
    EntityManager entities; 
    std::vector<ISystem*> systems; // TODO: Must replace with ordered map

public:
    // Entity management
    inline void addEntity(Entity* e) { entities.insert(e); };
    inline void deleteEntity(Entity* e) { entities.remove(e); };

    inline const std::set<Entity*>* getEntities() { return entities.getAll(); };
    inline const std::set<Entity*>* getEntities(COMP_TYPE t)
            { return entities.getByComponent(t); };
    inline std::set<Entity*>* getEntities(std::vector<COMP_TYPE>* cts)
            { return entities.getByComponents(cts); };

    // ISystem management
    inline void addSystem(ISystem* s) { systems.push_back(s); };

    // Execution of systems i.e. game step
    void runOnce();
};


#endif