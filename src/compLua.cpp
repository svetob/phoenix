#include <stdlib.h>
#include <string>

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

#include "component.h"
#include "compTypes.h"
#include "compLua.h"
#include "entity.h"
#include "luaMap.h"

/* TODO:
   Each Lua component should create a *static* entity
   in the Lua state. */

Lua::Lua(lua_State* L, const char* script, Entity* e)
{
    type = LUA;
    this->L = L;
    this->script = script;
    this->e = e;
}

void Lua::runScript()
{
    // Push script (function) name onto stack
    lua_getglobal(L, script);
    luaPushClass<Entity>(L, e, METADATA_ENTITY);

    // Call function with 1 arguments and 0 ret. args
    luaReportErrors(L, lua_pcall(L, 1, 0, 0));
}
