#ifndef World_h
#define World_h

#include <cstdio>
#include <list>
#include "Square.h"
#include "Camera.h"

class World
{
public: 

	~World();
	
	static World	*init();
	static World	*getInstance();
	static void		destroy();	
	void render();
	void update();	
	
private:

	void setup();
	World();
	void drawCube() ;
	void addFloor(float x, float y);
	static World	*instance;
	std::list<Square*> floorTiles;
	void drawFloor();
	void loadTextures();
    void deleteTextures();
	int previousTime;
	float fRotate;
	Camera camera;
	
		
		
};

#endif // Game_h