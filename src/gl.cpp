#include "gl.h"

ogl::GLContext* ogl::context = NULL;

bool ogl::initGL( int w, int h )
{
    // Init libraries
	if ( !glfwInit() )
    {
        //context = NULL;
        return false;
    }

	// Obtain window
    if ( !glfwOpenWindow( w, h, 8, 8, 8, 8, 24, 8, GLFW_WINDOW ) )
    {
        glfwTerminate();
        //context = NULL;
        return false;
    }

    // Assumed successful
    ogl::context = new ogl::GLContext();
    ogl::context->w = w;
    ogl::context->h = h;
    return true;
}

void ogl::setupGL( void )
{
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glClearDepth( 1.0 );
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_BLEND );
    //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDisable( GL_CULL_FACE );
    glewInit();
}

void ogl::closeGL()
{
	// Release resources
    glfwCloseWindow();
	glfwTerminate();
}
