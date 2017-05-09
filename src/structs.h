#ifndef STRUCTS
#define STRUCTS

#include <glm/glm.hpp>
#include <string>

//vertex struct with position and normal
struct Vertex {
    glm::vec3 pos, normal;
};

struct Bone {
   glm::mat4 relativeXForm, absoluteXForm;
   std::string parent; //index of parent
};

#endif // STRUCTS
