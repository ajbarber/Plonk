#include "MainGL.h"

MainGL::MainGL(int argc, char **argv)
{
    initGL(argc, argv);	
	loadTextures();
}

MainGL::~MainGL()
{
	deleteTextures();
}

void MainGL::drawSolidTriangle()
{  
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.1f, -0.6f);
    glVertex2f(0.7f, -0.6f);
    glVertex2f(0.4f, -0.1f);
    glEnd();
}

//void MainGL::update()
//{  
//    glClear(GL_COLOR_BUFFER_BIT);
//    drawSolidTriangle();   	
//	glutSwapBuffers();
//}


void MainGL::update()
{	
	
	Game *game = Game::getInstance();
	game->hero->render();	
	
	
	glutSwapBuffers();
	MainGL::checkErrors();
}


void MainGL::drawGame(int)
{	   
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glutDisplayFunc(MainGL::update);
	
	glutTimerFunc(33, drawGame, 0);		
	glutPostRedisplay();
	
}

void MainGL::initGL(int argc, char **argv)
{  
    glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);	
    glutCreateWindow("plonk");   
    glutInitWindowPosition(50,50);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);

}

bool MainGL::run() {    
    glutTimerFunc(100, MainGL::drawGame, 0);	
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



void MainGL::loadTextures() {
	
	Game *game = Game::getInstance();	
    game->hero = new Sprite(1);
    game->hero->setFrameSize(0.3f,0.3f);
	game->hero->setNumberOfFrames(1);
	GLfloat screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    game->hero->setPosition(0.0f,0.0f);
	//game->hero->setUseTransparency(false);
    game->hero->addTexture("/home/adam/git/plonk/data/png/shipsprite.png");    
	game->hero->setIsActive(true);
	game->hero->setIsVisible(true);
		
}

void MainGL::deleteTextures() {
	Game *game = Game::getInstance();	
    delete game->hero;
}






