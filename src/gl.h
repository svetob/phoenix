#ifndef _GL_H
#define _GL_H

#define GLEW_STATIC
#include <gl/glew.h>
#include <gl/glfw.h>

namespace ogl
{
    struct GLContext
    {
        int w;
        int h;
    };

    extern GLContext* context;

    void setupGL( void );
    bool initGL( int w, int h );
    void closeGL();
}

#endif