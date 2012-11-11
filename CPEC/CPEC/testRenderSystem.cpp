#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <vector>

#include "compDecl.h"
#include "sysDecl.h"
#include "gl.h"


TestRenderSystem::TestRenderSystem()
{
    //reqComps.push_back(POSITION);
    reqComps.push_back(RENDER);
}

void TestRenderSystem::update(const std::set<Entity*>* entities) 
{
    // Reset rendering surface
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Set camera position
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)ogl::context->w, (GLdouble)ogl::context->h, 0.0);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Get draw entities
    std::set<Entity*>::iterator it;
    glBegin(GL_QUADS);
    for (it = entities->begin(); it != entities->end(); ++it)
    {
        Entity* e = *it;
        Position* p = (Position*)e->getComponent(POSITION);
        
            glVertex3f(p->x,p->y,0);
            glVertex3f(p->x+10,p->y,0);
            glVertex3f(p->x+10,p->y+10,0);
            glVertex3f(p->x,p->y+10,0);
        
    }
    glEnd();

    // Swap buffer
    glfwSwapBuffers();
}
