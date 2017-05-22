#ifndef HERODRAWABLE_H
#define HERODRAWABLE_H

#include "gldrawable.h"

class HeroDrawable : public GLDrawable
{
public:
    HeroDrawable(const Drawing& drawing);
    virtual ~HeroDrawable() {}

    int bind();
};

#endif // HERODRAWABLE_H
