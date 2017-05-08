#include "floor.h"

Floor::Floor(const float width, const float depth)
{
    fillData(width, depth);
}

void Floor::fillData(const float width, const float depth) {
    float halfW = width/2.0f;
    float halfD = depth/2.0f;

    indices.resize(6);
    vertices.resize(4);
    glm::vec3 normal=glm::vec3(0,1,0);

    vertices[0].pos = glm::vec3(-halfW,0.01,-halfD); vertices[0].normal=normal;
    vertices[1].pos = glm::vec3(-halfW,0.01, halfD); vertices[1].normal=normal;
    vertices[2].pos = glm::vec3( halfW,0.01, halfD); vertices[2].normal=normal;
    vertices[3].pos = glm::vec3( halfW,0.01,-halfD); vertices[3].normal=normal;

    //fill indices array
    indices[0]=0;
    indices[1]=1;
    indices[2]=2;

    indices[3]=0;
    indices[4]=2;
    indices[5]=3;
}

