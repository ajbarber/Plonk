
#include "World.h"

using namespace std;

World *World::instance = 0;

World::World(): previousTime(0),fRotate(1.0)
{
	setup();
}

World::~World()
{
	
}

World *World::init()
{
	if(!World::instance)
	{
		World::instance = new World;				
		instance->previousTime = glutGet(GLUT_ELAPSED_TIME);
	}
	else
	{
		fprintf(stderr, "WARNING: World::init() has already been called.\n");
	}
	return World::instance;
}

//----------------------------------------------------------
World *World::getInstance()
{
	if(!instance)
	{
		return World::init();
	}
	else
		return World::instance;
}

//----------------------------------------------------------
void World::destroy()
{
	World::instance->deleteTextures();
	delete World::instance;
	World::instance = 0;
}

void World::setup()
{
	for (unsigned int x(0); x < WORLD_WIDTH / 128; x++)
    {
        for (unsigned int y(0); y < WORLD_HEIGHT / 128; y++)
        {
            addFloor(x * 128.f, y * 128.f);
        }
    }

	
}

void World::loadTextures() 
{	
	
}

void World::deleteTextures() 
{	
    
}

void World::render() 
{ 
	
	//drawCube();
	//drawCube();
	camera.draw(floorTiles);
	//render everything here;
	
}

void World::drawCube() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslatef(0.0f, 0.0f, -7.0f);
	glRotatef(fRotate, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f); 
	glVertex3f(-1.0f, 1.0f, -1.0f); 
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f); 
	glColor3f(1.0f, 0.5f, 0.0f); 
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f); 
	glVertex3f(-1.0f, -1.0f, -1.0f); 
	glVertex3f(1.0f, -1.0f, -1.0f); 
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f); 
	glColor3f(1.0f, 1.0f, 0.0f);  
	glVertex3f(1.0f, -1.0f, -1.0f); 
	glVertex3f(-1.0f, -1.0f, -1.0f); 
	glVertex3f(-1.0f, 1.0f, -1.0f); 
	glVertex3f(1.0f, 1.0f, -1.0f);  
	glColor3f(0.0f, 0.0f, 1.0f); 
	glVertex3f(-1.0f, 1.0f, 1.0f); 
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f); 
	glVertex3f(-1.0f, -1.0f, 1.0f); 
	glColor3f(1.0f, 0.0f, 1.0f); 
	glVertex3f(1.0f, 1.0f, -1.0f); 
	glVertex3f(1.0f, 1.0f, 1.0f);  
	glVertex3f(1.0f, -1.0f, 1.0f); 
	glVertex3f(1.0f, -1.0f, -1.0f); 
	glEnd();  
	fRotate -= 0.05f;
}

void World::update() 
{	
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (float)(currentTime - instance->previousTime) / 1000.0f;
	instance->previousTime = currentTime;
	
	//camera.update()
	//call in hero + npc update methods here	
}

void World::addFloor(float x, float y)
{ 		
	float z = 128.f;
    floorTiles.push_back(new Square(x,y,z,128.f, 0.f, 0.9f, 0.9f, 0.9f, 1.f));
}




