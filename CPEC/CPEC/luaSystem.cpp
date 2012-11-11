
#include "compLua.h"
#include "compTypes.h"
#include "sysDecl.h"

LuaSystem::LuaSystem()
{
    reqComps.push_back(LUA);
}

void LuaSystem::update(const std::set<Entity*>* entities)
{
    std::set<Entity*>::iterator it;
    for (it = entities->begin(); it != entities->end(); ++it)
    {
        Entity* e = *it;
        Lua* lua = (Lua*)e->getComponent(LUA);
        lua->runScript();
    }
}