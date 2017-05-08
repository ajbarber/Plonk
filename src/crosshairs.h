#ifndef CROSSHAIRS_H
#define CROSSHAIRS_H

#include <vector>
#include "drawing.h"

class CrossHair: public Drawing
{
public:
    CrossHair();

private:
    void fillData();
};

#endif // CROSSHAIRS_H
