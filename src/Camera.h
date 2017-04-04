#ifndef CAMERA_H
#define CAMERA_H

#include "Square.h"
#include <list>
#include "Frustum.h"
#include "Matrix4x4f.h"

class Camera
{
public:
	Camera();
	~Camera();
	
	
	void draw(std::list<Square*> &floorTiles);
	
private:
    void drawItem(const Square& o);
	float speed;
    float tolerance;
    float inertia;
	float x,y,z;
	void updateViewFrustum();
	
	Frustum viewFrustum;
	

};

#endif // CAMERA
