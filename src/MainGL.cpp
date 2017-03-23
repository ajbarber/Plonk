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

void MainGL::update()
{  
    glClear(GL_COLOR_BUFFER_BIT);
    drawSolidTriangle();
    glFlush();
}

void MainGL::drawGame(int)
{
	Game *game = Game::getInstance();
    //fprintf(stderr, "Test");	
	glutTimerFunc(33, drawGame, 0);	
	//MainGL::update();
	
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	game->hero->render();
	glutPostRedisplay();
}

void MainGL::initGL(int argc, char **argv)
{  
    glutInit(&argc, argv);
    glutCreateWindow("plonk");
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50,50);    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

bool MainGL::run() {    
    glutTimerFunc(100, MainGL::drawGame, 0);	
	
    glutMainLoop();
}


void MainGL::loadTextures() {
	Game *game = Game::getInstance();	
    game->hero = new Sprite(1);
    game->hero->setFrameSize(100.0f,125.0f);
	game->hero->setNumberOfFrames(1);
    game->hero->setPosition(50,50);
	//game->hero->setUseTransparency(false);
    game->hero->addTexture("/home/adam/git/plonk/data/png/shipsprite.png");    	
}

void MainGL::deleteTextures() {
	Game *game = Game::getInstance();	
    delete game->hero;
}






