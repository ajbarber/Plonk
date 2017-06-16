#ifndef STRUCTS
#define STRUCTS

#include <glm/glm.hpp>
#include <string>

//vertex struct with position and normal
struct Vertex {
    glm::vec3 pos, normal;
    glm::vec2 tex;
};

struct Bone {
   glm::mat4 worldToBone;
   glm::mat4 boneToParent;
   std::string parent; //index of parent  
};

#endif // STRUCTS
