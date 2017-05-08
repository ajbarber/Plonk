#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "drawing.h"


class Cube: public Drawing
{
public:
    Cube(float size);


private:
    void fillData(float size);
    //sphere vertex array and vertex buffer object IDs

};


#endif // CUBE_H
