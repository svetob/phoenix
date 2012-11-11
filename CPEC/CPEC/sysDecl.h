#ifndef _SYSDECL_H
#define _SYSDECL_H

#include "system.h"

// All systems here
class PerformanceMeasureSystem: public ISystem
{
public:
    int frames;
    double nextUpdate;
    double overtime;

    PerformanceMeasureSystem();
    void update(const std::set<Entity*>* entities);
};

class TestRenderSystem: public ISystem
{    
public:
    TestRenderSystem();
    void update(const std::set<Entity*>* entities);
};

class MovementSystem: public ISystem
{    
public:
    MovementSystem();
    void update(const std::set<Entity*>* entities);
};

class LuaSystem: public ISystem
{
public:
    LuaSystem();
    void update(const std::set<Entity*>* entities);
};

#endif