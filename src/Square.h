#ifndef SPRITE_H
#define SPRITE_H

#include "gl.h"
#include "Structs.h"
#include "Item.h"
#include <stdio.h>

class Square : public Item {

public :

	Square(float x,
		   float y,
		   float z,
		   float size,
		   float height,
		   float red,
		   float green, 
		   float blue, 
		   float alpha);
		   
	void draw() const;
	void outline();
	
private:

     unsigned int totalVertex;
     unsigned int totalIndexes;
	 Vertex vertices[4];
	 GLubyte indexes[6];
	 
};

#endif