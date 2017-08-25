#ifndef CROSSHAIRDRAWABLE_H
#define CROSSHAIRDRAWABLE_H

#include "gldrawable.h"

class CrossHairDrawable: public GLDrawable
{
public:
    CrossHairDrawable(const Drawing& drawing);
    void bindDrawing();
};

#endif // CROSSHAIRDRAWABLE_H
