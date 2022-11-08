#ifndef GLDRAWABLE_H
#define GLDRAWABLE_H

#include "gl.h"
#include "drawing.h"

class GLDrawable
{
public:
    GLDrawable(const Drawing &drawing);
    virtual ~GLDrawable();
    virtual void bindDrawing() = 0;
    virtual int bindTexture() { return 0; }
    virtual GLuint getVaoID();
    virtual GLuint getNumTriangles();
    virtual const Drawing& getDrawing() const;

protected:
    const Drawing &drawing;
    GLuint vaoID;
    GLuint numTriangles;
};

#endif // GLDRAWABLE_H
