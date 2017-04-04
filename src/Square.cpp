#include "Square.h"


Square::Square(float x,
			   float y,
			   float z,
			   float size, 
			   float height, 
			   float red, 
			   float green, 
			   float blue, 
			   float alpha): Item(x, y, z)
{
    totalVertex = 4;
    totalIndexes  = 6;

    float alfSize = size / 2.f;

    vertices[0].location[X_POS] = alfSize;
    vertices[0].location[Y_POS] = height;
    vertices[0].location[Z_POS] = -alfSize;
    vertices[0].normal[X_POS]   = 0.f;
    vertices[0].normal[Y_POS]   = 1.f;
    vertices[0].normal[Z_POS]   = 0.f;
    vertices[0].tex[U_POS]      = 0.f;
    vertices[0].tex[V_POS]      = 0.f;

    vertices[1].location[X_POS] = -alfSize;
    vertices[1].location[Y_POS] = height;
    vertices[1].location[Z_POS] = -alfSize;
    vertices[1].normal[X_POS]   = 0.f;
    vertices[1].normal[Y_POS]   = 1.f;
    vertices[1].normal[Z_POS]   = 0.f;
    vertices[1].tex[U_POS]      = 0.f;
    vertices[1].tex[V_POS]      = height;

    vertices[2].location[X_POS] = -alfSize;
    vertices[2].location[Y_POS] = height;
    vertices[2].location[Z_POS] = alfSize;
    vertices[2].normal[X_POS]   = 0.f;
    vertices[2].normal[Y_POS]   = 1.f;
    vertices[2].normal[Z_POS]   = 0.f;
    vertices[2].tex[U_POS]      = alfSize;
    vertices[2].tex[V_POS]      = height;

    vertices[3].location[X_POS] = alfSize;
    vertices[3].location[Y_POS] = height;
    vertices[3].location[Z_POS] = alfSize;
    vertices[3].normal[X_POS]   = 0.f;
    vertices[3].normal[Y_POS]   = 1.f;
    vertices[3].normal[Z_POS]   = 0.f;
    vertices[3].tex[U_POS]      = alfSize;
    vertices[3].tex[V_POS]      = 0.f;

    indexes[0] = 0;
    indexes[1] = 1;
    indexes[2] = 2;

    indexes[3] = 2;
    indexes[4] = 3;
    indexes[5] = 0;

    for (int i = 0; i < totalVertex; i++)
    {
        vertices[i].color[0] = red;
        vertices[i].color[1] = green;
        vertices[i].color[2] = blue;
        vertices[i].color[3] = alpha;
    }
    
}

void Square::draw() const
{  
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//		
//		
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glTranslatef(0.0f, 0.0f, -7.0f);
//	glRotatef(1.0f, 1.0f, 1.0f, 1.0f);
//	glBegin(GL_QUADS);
//	glColor3f(0.0f, 1.0f, 0.0f);
//	glVertex3f(1.0f, 1.0f, -1.0f); 
//	glVertex3f(-1.0f, 1.0f, -1.0f); 
//	glVertex3f(-1.0f, 1.0f, 1.0f);
//	glVertex3f(1.0f, 1.0f, 1.0f); 
//	glColor3f(1.0f, 0.5f, 0.0f); 
//	glVertex3f(1.0f, -1.0f, 1.0f);
//	glVertex3f(-1.0f, -1.0f, 1.0f); 
//	glVertex3f(-1.0f, -1.0f, -1.0f); 
//	glVertex3f(1.0f, -1.0f, -1.0f); 
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glVertex3f(1.0f, 1.0f, 1.0f);
//	glVertex3f(-1.0f, 1.0f, 1.0f);
//	glVertex3f(-1.0f, -1.0f, 1.0f);
//	glVertex3f(1.0f, -1.0f, 1.0f); 
//	glColor3f(1.0f, 1.0f, 0.0f);  
//	glVertex3f(1.0f, -1.0f, -1.0f); 
//	glVertex3f(-1.0f, -1.0f, -1.0f); 
//	glVertex3f(-1.0f, 1.0f, -1.0f); 
//	glVertex3f(1.0f, 1.0f, -1.0f);  
//	glColor3f(0.0f, 0.0f, 1.0f); 
//	glVertex3f(-1.0f, 1.0f, 1.0f); 
//	glVertex3f(-1.0f, 1.0f, -1.0f);
//	glVertex3f(-1.0f, -1.0f, -1.0f); 
//	glVertex3f(-1.0f, -1.0f, 1.0f); 
//	glColor3f(1.0f, 0.0f, 1.0f); 
//	glVertex3f(1.0f, 1.0f, -1.0f); 
//	glVertex3f(1.0f, 1.0f, 1.0f);  
//	glVertex3f(1.0f, -1.0f, 1.0f); 
//	glVertex3f(1.0f, -1.0f, -1.0f); 
//	glEnd();  
	
	
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < totalIndexes; i ++)
    {
        glColor4f(vertices[indexes[i]].color[0], vertices[indexes[i]].color[1], vertices[indexes[i]].color[2], vertices[indexes[i]].color[3]);
        glNormal3f(vertices[indexes[i]].normal[0], vertices[indexes[i]].normal[1], vertices[indexes[i]].normal[2]);
        glVertex3f(vertices[indexes[i]].location[0], vertices[indexes[i]].location[1], vertices[indexes[i]].location[2]);
    }
    glEnd();
   
}

void Square::outline()
{
    for (unsigned int i = 0; i < totalIndexes; i ++)
    {
        if (i%3 == 0)
        {
            if (i != 0)
            {
                glEnd();
            }
            glBegin(GL_LINE_LOOP);
        }
        glColor4f(vertices[indexes[i]].color[0], vertices[indexes[i]].color[1], vertices[indexes[i]].color[2], vertices[indexes[i]].color[3]);
        glNormal3f(vertices[indexes[i]].normal[0], vertices[indexes[i]].normal[1], vertices[indexes[i]].normal[2]);
        glVertex3f(vertices[indexes[i]].location[0], vertices[indexes[i]].location[1], vertices[indexes[i]].location[2]);
    }
    glEnd();
}

