#include "MainGL.h"

MainGL::MainGL(int argc, char **argv)
{
    initGL(argc, argv);		
}

MainGL::~MainGL()
{	
}

//void MainGL::update()
//{  
//    glClear(GL_COLOR_BUFFER_BIT);
//    drawSolidTriangle();   	
//	glutSwapBuffers();
//}

void MainGL::updateAndRender()
{		
	glLoadIdentity();

    // Isometric angle
	glRotatef(30.f, 1.f, 0.f, 0.f);
	glRotatef(-45.f, 0.f, 1.f, 0.f);

	// Scale
	glScaled(sqrt(1/2.0), sqrt(1/3.0), sqrt(1/2.0));
		
	World *world = World::getInstance();
	
	world->update();
	
	world->render();		
	
	glutSwapBuffers();
	
	MainGL::checkErrors();
}


void MainGL::gameLoop(int)
{	   	
	glutTimerFunc(33, gameLoop, 0);		
	glutPostRedisplay();	
}


void MainGL::initGL(int argc, char **argv)
{  
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);	
    glutInitWindowPosition(50,50);
    glutCreateWindow("plonk");   
	
	glutDisplayFunc(MainGL::updateAndRender);	
	
   	testinitFromLittleWorld();
	//testinitfromBook();
		
	setupWindow(SCREEN_WIDTH,SCREEN_HEIGHT);	  
				
}

void MainGL::testinitFromLittleWorld()
{
	//Setup rendering
    glShadeModel(GL_SMOOTH);
	
    glCullFace(GL_FRONT);
    //glEnable(GL_POINT_SMOOTH);
    //glEnable(GL_LINE_SMOOTH);
    //glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//
    // Default values
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDepthMask(GL_FALSE);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
//
//    // Clear values
    glClearDepth(GL_ONE);
    glClearStencil(GL_ZERO);
    glClearColor(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
}

void MainGL::testinitfromBook()
{
	 glShadeModel(GL_SMOOTH);
     glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  
	 glClearDepth(1.0f); 
	 glEnable(GL_DEPTH_TEST);  
	 glDepthFunc(GL_LEQUAL); 
	 glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void MainGL::setupWindow(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float space;

    if (width / height > SCREEN_WIDTH / SCREEN_HEIGHT)
    {
        // TODO compute back and front clip plane better
        space = abs(((SCREEN_HEIGHT / (height / width)) - SCREEN_WIDTH) / 2.f);
        glOrtho
        (
            SCREEN_WIDTH / -2.f - space,
            SCREEN_WIDTH / 2.f + space,
            SCREEN_HEIGHT / -2.f,
            SCREEN_HEIGHT / 2.f,
            SCREEN_HEIGHT * (SCREEN_HEIGHT / height) * -1,
            SCREEN_HEIGHT
        );
    }
    else
    {
        space = abs(((SCREEN_WIDTH / (width / height)) - SCREEN_HEIGHT) / 2.f);
        glOrtho
        (
            SCREEN_WIDTH / -2.f,
            SCREEN_WIDTH / 2.f,
            SCREEN_HEIGHT / -2.f - space,
            SCREEN_HEIGHT / 2.f + space,
            SCREEN_HEIGHT * (SCREEN_WIDTH / width) * -1.f,
            SCREEN_HEIGHT
        );
    }
    //swap gluPerspective call below for commented section above;
	//gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool MainGL::run() {   
	
    glutTimerFunc(100, MainGL::gameLoop, 0);	
	glutMainLoop();
}

bool MainGL::checkErrors()
{
	bool retVal = false;
	GLenum	gl_error;

	//-- Check for GL errors
	gl_error = glGetError( );
	if( gl_error != GL_NO_ERROR )
	{
		fprintf(stderr, "ERROR!!! OpenGL error: %s\n", gluErrorString(gl_error) );
		retVal = true;
	}

	return retVal;
}








