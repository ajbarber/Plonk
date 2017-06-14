#ifndef CUBEDRAWABLE_H
#define CUBEDRAWABLE_H

#include "gldrawable.h"

class CubeDrawable : public GLDrawable
{
public:
    CubeDrawable(const Drawing& drawing);
    virtual ~CubeDrawable() {}

    int bind();

};

#endif // CUBEDRAWABLE_H
