#include "crosshairs.h"

CrossHair::CrossHair()
{
    CrossHair::fillData();
}

void CrossHair::fillData()
{
    //setup vao and vbo stuff for the light position crosshair
    points.resize(6);
    points[0] = glm::vec3(-0.5f,0,0);
    points[1] = glm::vec3(0.5f,0,0);
    points[2] = glm::vec3(0, -0.5f,0);
    points[3] = glm::vec3(0, 0.5f,0);
    points[4] = glm::vec3(0,0, -0.5f);
    points[5] = glm::vec3(0,0, 0.5f);
}

