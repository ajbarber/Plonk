#include "Camera.h"

Camera::Camera()
{
	speed     = 50.f;
    tolerance = 50.f;
    inertia   = 0.3f;

    x = 0.f;
    y = 0.f;
    z = 0.f;
}

Camera::~Camera()
{
}

void Camera::updateViewFrustum()
{
    Matrix4x4f projMatrix;
    Matrix4x4f viewMatrix;

    glGetFloatv(GL_PROJECTION_MATRIX, projMatrix.m);
    glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix.m);

    viewFrustum.update(projMatrix * viewMatrix);
}


void Camera::draw(std::list<Square*> &floorTiles) {
//	
	glPushMatrix();
    glTranslatef(x * -1.f,  y * -1.f, z * -1.f);
//	
	updateViewFrustum();
	 
	GLfloat ambientColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	// STEP 0: setup
    // =============

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
//
    glClear(GL_COLOR_BUFFER_BIT);

    //glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);


    // STEP 1: render depth
    // ====================

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
//
    glClear(GL_DEPTH_BUFFER_BIT);
//
    glFrontFace(GL_CW);
   
	for (std::list<Square*>::iterator it = floorTiles.begin(); it != floorTiles.end(); ++it)
    {
        drawItem(**it);
    }
	glDepthMask(GL_FALSE);
//	
	glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
	glPopMatrix();

	
}
void Camera::drawItem(const Square& o)
{   
	glPushMatrix();
	glTranslatef(o.getX(), o.getY(), o.getZ());
	o.draw();
	glPopMatrix();
}


