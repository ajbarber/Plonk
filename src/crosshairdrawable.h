#ifndef CROSSHAIRDRAWABLE_H
#define CROSSHAIRDRAWABLE_H

#include "gldrawable.h"

class CrossHairDrawable: public GLDrawable
{
public:
    CrossHairDrawable(const Drawing& drawing);
    int bind();
};

#endif // CROSSHAIRDRAWABLE_H
