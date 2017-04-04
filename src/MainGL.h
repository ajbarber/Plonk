#ifndef MainGL_h
#define MainGL_h

#include "gl.h"
#include "World.h"
#include "Square.h"
#include <stdio.h>
#include "Structs.h"

class MainGL
{
public:
    MainGL(int argc = 0, char **argv = 0);
    ~MainGL();
    
    bool run();
 
    static void gameLoop(int);
	static void drawSolidTriangle();
	static void updateAndRender();
	static void testDisplay();
    
private:

    void initGL(int argc = 0, char **argv = 0);	 
    void render();
	static bool checkErrors();	
	void setupWindow(GLsizei width, GLsizei height);
	void testinitfromBook();
	void testinitFromLittleWorld();
   
    
    
};


#endif // mainGL_h