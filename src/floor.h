#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include "drawing.h"

class Floor: public Drawing
{
public:
    Floor(const float width, const float depth);

private:
    void fillData(const float width, const float depth);

};

#endif // FLOOR_H
