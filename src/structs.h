#ifndef STRUCTS
#define STRUCTS

#include <glm/glm.hpp>
#include <string>

//vertex struct with position and normal
struct Vertex {
    glm::vec3 pos, normal;
    glm::vec2 tex;
};

#endif // STRUCTS
