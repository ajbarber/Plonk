#ifndef GLDRAWABLE_H
#define GLDRAWABLE_H

#include "gl.h"
#include "drawing.h"


class GLDrawable
{
public:    
    GLDrawable(const Drawing &drawing);

    virtual ~GLDrawable();
    virtual int bind() = 0;
    virtual GLuint getVaoID();
    virtual GLuint getNumTriangles();


protected:
    const Drawing &drawing;
    GLuint vaoID;
    GLuint numTriangles;



};

#endif // GLDRAWABLE_H