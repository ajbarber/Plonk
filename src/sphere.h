#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "drawing.h"


class Sphere: public Drawing
{
public:
    Sphere(float radius, unsigned int slices, unsigned int stacks);  


private:
    void fillData(float radius, unsigned int slices, unsigned int stacks);
    //sphere vertex array and vertex buffer object IDs

};

#endif // SPHERE_H
