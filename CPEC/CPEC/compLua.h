#ifndef _COMPLUA_H
#define _COMPLUA_H

#include <stdlib.h>
#include <string>

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

#include "component.h"
#include "entity.h"
#include "luaMap.h"


class Lua: public IComponent
{
public:
    lua_State* L;
    const char* script;
    Entity* e;

    Lua(lua_State* L, const char* script, Entity* e);
    void runScript();
};

#endif
