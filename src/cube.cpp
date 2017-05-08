#include "cube.h"

Cube::Cube(float size)
{
    Cube::fillData(size);
}


void Cube::fillData(float size) {
    float halfSize = size/2.0f;
    glm::vec3 positions[8];
    positions[0]=glm::vec3(-halfSize,-halfSize,-halfSize);
    positions[1]=glm::vec3( halfSize,-halfSize,-halfSize);
    positions[2]=glm::vec3( halfSize, halfSize,-halfSize);
    positions[3]=glm::vec3(-halfSize, halfSize,-halfSize);
    positions[4]=glm::vec3(-halfSize,-halfSize, halfSize);
    positions[5]=glm::vec3( halfSize,-halfSize, halfSize);
    positions[6]=glm::vec3( halfSize, halfSize, halfSize);
    positions[7]=glm::vec3(-halfSize, halfSize, halfSize);

    glm::vec3 normals[6];
    normals[0]=glm::vec3(-1.0,0.0,0.0);
    normals[1]=glm::vec3(1.0,0.0,0.0);
    normals[2]=glm::vec3(0.0,1.0,0.0);
    normals[3]=glm::vec3(0.0,-1.0,0.0);
    normals[4]=glm::vec3(0.0,0.0,1.0);
    normals[5]=glm::vec3(0.0,0.0,-1.0);

    indices.resize(36);
    vertices.resize(36);

    //fill indices array
    GLushort* id=&indices[0];
    //left face
    *id++ = 7; 	*id++ = 3; 	*id++ = 4;
    *id++ = 3; 	*id++ = 0; 	*id++ = 4;

    //right face
    *id++ = 2; 	*id++ = 6; 	*id++ = 1;
    *id++ = 6; 	*id++ = 5; 	*id++ = 1;

    //top face
    *id++ = 7; 	*id++ = 6; 	*id++ = 3;
    *id++ = 6; 	*id++ = 2; 	*id++ = 3;
    //bottom face
    *id++ = 0; 	*id++ = 1; 	*id++ = 4;
    *id++ = 1; 	*id++ = 5; 	*id++ = 4;

    //front face
    *id++ = 6; 	*id++ = 4; 	*id++ = 5;
    *id++ = 6; 	*id++ = 7; 	*id++ = 4;
    //back face
    *id++ = 0; 	*id++ = 2; 	*id++ = 1;
    *id++ = 0; 	*id++ = 3; 	*id++ = 2;


    for(int i=0;i<36;i++) {
        int normal_index = i/6;
        vertices[i].pos=positions[indices[i]];
        vertices[i].normal=normals[normal_index];
        indices[i]=i;
    }
}
