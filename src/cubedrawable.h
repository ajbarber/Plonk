#ifndef CUBEDRAWABLE_H
#define CUBEDRAWABLE_H

#include "gldrawable.h"
#include "gl.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class CubeDrawable : public GLDrawable
{
public:
    CubeDrawable(const Drawing& drawing);
    virtual ~CubeDrawable() {}

    int bind();

};

#endif // CUBEDRAWABLE_H
