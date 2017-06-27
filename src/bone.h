#ifndef BONE_H
#define BONE_H

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <memory>


class Bone
{
public:

    std::string name;
    std::string parentName;
    glm::mat4 worldToBone;
    glm::mat4 boneToParent;
    double weight;
    Bone *parent;

    glm::mat4 getTransform(float seconds, const aiAnimation& animation);

};

#endif // BONE_H
