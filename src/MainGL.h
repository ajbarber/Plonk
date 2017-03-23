#ifndef MainGL_h
#define MainGL_h

#include "gl.h"
#include "Game.h"
#include "Sprite.h"
#include <stdio.h>

class MainGL
{
public:
    MainGL(int argc = 0, char **argv = 0);
    ~MainGL();
    
    bool run();
 
    static void drawGame(int);
	static void drawSolidTriangle();
	static void update();
    
private:

    void initGL(int argc = 0, char **argv = 0);
    void loadTextures();
    void deleteTextures();
    void render();

    Sprite *hero;
    
    
};


#endif // mainGL_h