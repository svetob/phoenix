#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

#include "entity.h"
#include "compDecl.h"
#include "luaMap.h"



template <class C> C* l_CheckClass(lua_State * l, int n, const char* metadata_type)
{
    //TODO: Assert n args
    // Check that the value is a metadata of type "luaL_Entity"
    return *(C**)luaL_checkudata(l, n, metadata_type);
}


//-----------------------------------------------------
// Lua mapping of Entity class
//-----------------------------------------------------
int l_Entity_constructor(lua_State* L)
{
    //TODO: Assert n args
    const char* name = luaL_checkstring(L, 1);
    lua_pop(L, 1);

    // Create a new userdata in Lua, which points to an Entity object
    Entity** userdata = (Entity**)lua_newuserdata(L, sizeof(Entity*));
    *userdata = new Entity(name);

    // Create metatable
    luaL_getmetatable(L, METADATA_ENTITY);
    // Map metatable to userdata
    lua_setmetatable(L, -2);

    // Return userdata mapped to metatable
    return 1;
}

int l_Entity_destructor(lua_State* L)
{
    //TODO: Assert n args
    //Entity* e = l_CheckClass<Entity>(L, 1, METADATA_ENTITY);
    //delete e;
    
    //std::cout << "Entity destructored" << std::endl;
    lua_pop(L, 1);

    return 0;
}

int l_Entity_name(lua_State* L)
{
    //TODO: Assert n args
    Entity* e = l_CheckClass<Entity>(L, 1, METADATA_ENTITY);
    lua_pop(L, 1);

    // Return name
    lua_pushstring(L, e->getName());

    return 1;
}

int l_Entity_getPosition(lua_State* L)
{
    //TODO: Assert n args
    Entity* e = l_CheckClass<Entity>(L, 1, METADATA_ENTITY);
    lua_pop(L, 1);

    // Return name
    Position* pos = (Position*)e->getComponent(POSITION);
    luaPushClass<Position>(L, pos, METADATA_POSITION);

    return 1;
}

int l_Entity_getMovement(lua_State* L)
{
    //TODO: Assert n args
    Entity* e = l_CheckClass<Entity>(L, 1, METADATA_ENTITY);
    lua_pop(L, 1);

    // Return name
    Movement* pos = (Movement*)(e->getComponent(MOVEMENT));
    luaPushClass<Movement>(L, pos, METADATA_MOVEMENT);

    return 1;
}


//-----------------------------------------------------
// Lua mapping of Position component
//-----------------------------------------------------
int l_Position_constructor(lua_State* L)
{
    //TODO: Assert n args
    coord x = (coord)luaL_checknumber(L, 1);
    coord y = (coord)luaL_checknumber(L, 2);
    lua_pop(L, 2);

    // Create a new userdata in Lua, which points to an Entity object
    Position** userdata = (Position**)lua_newuserdata(L, sizeof(Position*));
    *userdata = new Position(x, y);

    // Create metatable
    luaL_getmetatable(L, METADATA_POSITION);
    // Map metatable to userdata
    lua_setmetatable(L, -2);

    // Return userdata mapped to metatable
    return 1;
}

int l_Position_get(lua_State* L)
{
    //TODO: Assert n args

    Position* pos = l_CheckClass<Position>(L, 1, METADATA_POSITION);
    lua_pop(L, 1);

    lua_pushnumber(L, pos->x);
    lua_pushnumber(L, pos->y);

    return 2;
}

int l_Position_set(lua_State* L)
{
    //TODO: Assert n args

    Position* pos = l_CheckClass<Position>(L, 1, METADATA_POSITION);
    coord x = (coord)luaL_checknumber(L, 2);
    coord y = (coord)luaL_checknumber(L, 3);
    lua_pop(L, 3);

    pos->set(x, y);
    return 0;
}

int l_Position_destructor(lua_State* L)
{
    //TODO: Assert n args
    //Position* pos = l_CheckClass<Position>(L, 1, METADATA_POSITION);
    //delete pos;
    
    //std::cout << "Position destructored" << std::endl;
    lua_pop(L, 1);

    return 0;
}


//-----------------------------------------------------
// Lua mapping of Movement component
//-----------------------------------------------------
int l_Movement_constructor(lua_State* L)
{
    //TODO: Assert 1 args
    Position* pos = l_CheckClass<Position>(L, 1, METADATA_POSITION);

    // Create a new userdata in Lua, which points to an Entity object
    Movement** userdata = (Movement**)lua_newuserdata(L, sizeof(Movement*));
    *userdata = new Movement(pos);
    lua_pop(L, 1);

    // Create metatable
    luaL_getmetatable(L, METADATA_MOVEMENT);
    // Map metatable to userdata
    lua_setmetatable(L, -2);

    // Return userdata mapped to metatable
    return 1;
}
int l_Movement_get(lua_State* L)
{
    //TODO: Assert n args

    Movement* mov = l_CheckClass<Movement>(L, 1, METADATA_MOVEMENT);
    lua_pop(L, 1);

    lua_pushnumber(L, mov->mx);
    lua_pushnumber(L, mov->my);

    return 2;
}

int l_Movement_set(lua_State* L)
{
    //TODO: Assert n args

    Movement* mov = l_CheckClass<Movement>(L, 1, METADATA_MOVEMENT);
    coord dx = (coord)luaL_checknumber(L, 2);
    coord dy = (coord)luaL_checknumber(L, 3);
    lua_pop(L, 3);

    mov->setVector(dx, dy);
    return 0;
}


int l_Movement_destructor(lua_State* L)
{
    //TODO: Assert n args
    //Movement* pos = l_CheckClass<Movement>(L, 1, METADATA_MOVEMENT);
    //delete pos;
    //std::cout << "Movement destructored" << std::endl;
    lua_pop(L, 1);

    return 0;
}

// ------------------------------------------------------
// Mapped functions to classes
// Check here for the Lua API! :)
// ------------------------------------------------------
const luaL_Reg lua_Regs_Entity[] = 
{
    {"new", l_Entity_constructor},
    {"name", l_Entity_name},
    {"getPosition", l_Entity_getPosition},
    {"getMovement", l_Entity_getMovement},
    //{"__gc", l_Entity_destructor},
    {NULL, NULL}
};

const luaL_Reg lua_Regs_Position[] = 
{
    {"new", l_Position_constructor},
    {"get", l_Position_get},
    {"set", l_Position_set},
    //{"__gc", l_Position_destructor},
    {NULL, NULL}
};

const luaL_Reg lua_Regs_Movement[] = 
{
    {"new", l_Movement_constructor},
    {"get", l_Movement_get},
    {"set", l_Movement_set},
    //{"__gc", l_Movement_destructor},
    {NULL, NULL}
};

//-----------------------------------------------------
// Lua bridge
//-----------------------------------------------------

// Returns true if error encountered
bool luaReportErrors(lua_State *L, int status)
{
    if ( status!=0 ) {
        std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // remove error message
        return true;
    }
    return false;
}

void luaMapClasses(lua_State* L)
{
    // Entity
    luaL_newmetatable(L, METADATA_ENTITY);
    luaL_setfuncs(L, lua_Regs_Entity, NULL);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_setglobal(L, "Entity");

    // Position
    luaL_newmetatable(L, METADATA_POSITION);
    luaL_setfuncs(L, lua_Regs_Position, NULL);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_setglobal(L, "Position");

    // Movement
    luaL_newmetatable(L, METADATA_MOVEMENT);
    luaL_setfuncs(L, lua_Regs_Movement, NULL);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_setglobal(L, "Movement");
}

bool luaLoadFile(lua_State* L, const char* file)
{
    std::cerr << "-- Loading file: " << file << std::endl;
    int s = luaL_loadfile(L, file);
    if (s != 0)
    {
        // File load failed
        luaReportErrors(L, s);
        return false;
    }
    else
    {
        // Execute file and return result
        return luaReportErrors( L, lua_pcall(L, 0, 0, 0) );
    }
}


lua_State* luaNewState()
{
     // Create new Lua state
    lua_State *L = luaL_newstate();

    // Open standard libraries
    luaL_openlibs(L);

    return L;
}
