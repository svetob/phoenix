#ifndef _LUAMAP_H
#define _LUAMAP_H

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

// ------------------------------------------------------
// Metadata types for Lua-mapped classes 
// ------------------------------------------------------
#define METADATA_ENTITY "luaL_Entity"
#define METADATA_POSITION "luaL_Position"
#define METADATA_MOVEMENT "luaL_Movement"

// ------------------------------------------------------
// Lua bridge
// ------------------------------------------------------

// Create a new Lua state
lua_State* luaNewState();

bool luaReportErrors(lua_State *L, int status);
bool luaLoadFile(lua_State* L, const char* file);
void luaMapClasses(lua_State* L);

template <class C> void luaPushClass(lua_State* L, C* c, const char* metadata_type)
{
    // Create a new userdata in Lua, which points to a C instance
    C** userdata = (C**)lua_newuserdata(L, sizeof(C*));
    *userdata = c;

    // Create metatable
    luaL_getmetatable(L, metadata_type);
    // Map metatable to userdata
    lua_setmetatable(L, -2);
}

#endif