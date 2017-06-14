#ifndef HERODRAWABLE_H
#define HERODRAWABLE_H

#include "gldrawable.h"

class HeroBodyPartDrawable : public GLDrawable
{
public:
    HeroBodyPartDrawable(const Drawing& drawing);
    virtual ~HeroBodyPartDrawable() {}

    int bind();

    bool checkErrors();
};

#endif // HERODRAWABLE_H
