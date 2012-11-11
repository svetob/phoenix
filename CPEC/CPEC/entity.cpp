#include "entity.h"

#include <vector>
#include <memory> // for allocator

Entity::Entity(const char* name)
{
    this->name = name;
    id = id_gen++;
}


