#ifndef FLOORDRAWABLE_H
#define FLOORDRAWABLE_H

#include "gldrawable.h"

class FloorDrawable: public GLDrawable
{
public:
    FloorDrawable(const Drawing& drawing);

    int bindDrawing();

};

#endif // FLOORDRAWABLE_H
