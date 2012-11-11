#ifndef _ENTITY_H
#define _ENTITY_H

#include <vector>

#include "component.h"
#include "componentStore.h"

class EntityTemplate
{
    char* name;
    std::vector<COMP_TYPE> componentTypes;
};

static int id_gen = 0;

class Entity
{
  private:
    int id;
    const char* name; // We will have too many types to define statically
    ComponentStore components;

  public:
    // TODO: Add constructor taking a configurator object
    Entity(const char* name);

    inline const char* getName() { return name; };
    inline int getId() { return id; };

    // Adds the given component
    // TODO: Assert if component already exists
    inline void addComponent(IComponent* c) { components.add(c); };
    
    // Returns NULL if no such component, component pointer otherwise
    inline IComponent* getComponent(COMP_TYPE ct) { return components.get(ct); };

    inline bool hasComponent(COMP_TYPE ct) { return components.get(ct) != NULL ;};
    inline bool hasComponents(std::vector<COMP_TYPE>* cts) { return components.hasAll(cts); };

    inline std::map<COMP_TYPE, IComponent*>::iterator getComponentIterator()
    { return components.getIterator(); };
    inline std::map<COMP_TYPE, IComponent*>::iterator getComponentIteratorEnd()
    { return components.getIteratorEnd(); };

};

#endif