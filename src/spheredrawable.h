#ifndef SPHEREDRAWABLE_H
#define SPHEREDRAWABLE_H

#include "gldrawable.h"
#include "gl.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class SphereDrawable: public GLDrawable
{
public:
    SphereDrawable(const Drawing& drawing);

    int bind();

};

#endif // SPHEREDRAWABLE_H
