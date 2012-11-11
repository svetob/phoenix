#include <time.h>
#include <sstream>
#include <vector>

#include <GL/glfw.h>

#include "world.h"
#include "sysDecl.h"

PerformanceMeasureSystem::PerformanceMeasureSystem()
{
    frames = 0;
    overtime = 0;
    nextUpdate = clock() + 1 * CLOCKS_PER_SEC;
}

void PerformanceMeasureSystem::update(const std::set<Entity*>* entities)
{
    double fps;
        
    ++frames;
    overtime = clock() - nextUpdate;
    if (overtime > 0)
    {
        fps = frames / (float)(1+ (float)overtime/(float)CLOCKS_PER_SEC);
        frames = 0;
        nextUpdate = clock() + 1 * CLOCKS_PER_SEC;

        std::stringstream ss;
        ss << "Entities: " << entities->size() << "  FPS: " << fps;
        glfwSetWindowTitle(ss.str().data());

    }
}