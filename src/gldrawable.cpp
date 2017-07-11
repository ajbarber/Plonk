#include "gldrawable.h"

GLDrawable::GLDrawable(const Drawing &drawing): drawing(drawing)
{

}

GLDrawable::~GLDrawable()
{

}

GLuint GLDrawable::getVaoID()
{
    return this->vaoID;
}

GLuint GLDrawable::getNumTriangles()
{
    return this->numTriangles;
}

const Drawing& GLDrawable::getDrawing() const {
    return drawing;
}


