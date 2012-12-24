#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

#include "gl.h"
#include "world.h"
#include "compDecl.h"
#include "compLua.h"
#include "sysDecl.h"

#include "luaMap.h"
#include "sysDecl.h"


Entity* genEntity(lua_State* L)
{
    Entity* e = new Entity("Rect");

    Position* pos = new Position(
            (coord)(rand() % ogl::context->w),
            (coord)(rand() % ogl::context->h));
    e->addComponent(pos);

    Movement* mov = new Movement(pos);
    mov->mx = (((coord) (rand() % 2000)) / 500.0) - 2;
    mov->my = (((coord) (rand() % 2000)) / 500.0) - 2;
    e->addComponent(mov);

    Render* r = new Render();
    r->visible = true;
    e->addComponent(r);

    Lua* lua = new Lua(L, "bounce", e);
    e->addComponent(lua);

    return e;
}


int main (int argc, char** argv)
{
    World* world;
    lua_State* L;

    // Init Lua state, connect Lua API
    L = luaNewState();
    luaMapClasses(L);

    // Load test file
    luaLoadFile(L, "lua/entity_myname.lua");
    
    // Init graphics
    if ( !ogl::initGL(480,640) )
    {
        exit( EXIT_FAILURE );
    }
    ogl::setupGL();

    // Create world
    world = new World();
    world->addSystem(new TestRenderSystem());
    world->addSystem(new PerformanceMeasureSystem());
    world->addSystem(new MovementSystem());
    world->addSystem(new LuaSystem());

    for (int i = 0; i < 5; i++)
    {
        world->addEntity(genEntity(L));
    }

    // Game loop
    bool runGameLoop = true;
    
    // Enter game
    srand( time( NULL ) );
    while ( runGameLoop )
    {
        world->runOnce();

        // Check for herpderp
        if ( glfwGetKey( 'A' ) )
        {
            // Add entity
            world->addEntity(genEntity(L));
        }

        // Check for exit
        if ( glfwGetKey( GLFW_KEY_ESC ) )
        {
            runGameLoop = 0;
        }
    }

    return 0;
}