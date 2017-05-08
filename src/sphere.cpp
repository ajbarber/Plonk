#include "sphere.h"

Sphere::Sphere(float radius, unsigned int slices, unsigned int stacks)
{
    Sphere::fillData(radius, slices, stacks);
}


void Sphere::fillData(float radius, unsigned int slices, unsigned int stacks) {
    float const R = 1.0f/(float)(slices-1);
    float const S = 1.0f/(float)(stacks-1);

    for(size_t r = 0; r < slices; ++r) {
        for(size_t s = 0; s < stacks; ++s) {
            float const y = (float)(sin( -M_PI_2 + M_PI * r * R ));
            float const x = (float)(cos(2*M_PI * s * S) * sin( M_PI * r * R ));
            float const z = (float)(sin(2*M_PI * s * S) * sin( M_PI * r * R ));

            Vertex v;
            v.pos = glm::vec3(x,y,z)*radius;
            v.normal = glm::normalize(v.pos);
            vertices.push_back(v);
            push_indices(stacks, r, s, indices);
        }
    }
}





