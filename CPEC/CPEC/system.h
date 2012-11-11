#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <vector>
#include <set>

#include "component.h"
#include "entity.h"


class ISystem
{
  protected:
    std::vector<COMP_TYPE> reqComps;

  public:
    virtual void update(const std::set<Entity*>* entities) = 0;
    inline std::vector<COMP_TYPE>* getRequiredComponents() { return &reqComps; };

};

#endif