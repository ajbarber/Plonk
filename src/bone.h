#ifndef BONE_H
#define BONE_H

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <memory>


class Bone
{
public:

    Bone() : parent(nullptr) {}

    Bone(Bone* bone);
    std::string name;
    std::string parentName;
    glm::mat4 worldToBone;
    glm::mat4 boneToParent;
    glm::mat4 inverseGlobal;
    std::shared_ptr<Bone> parent;

    glm::mat4 getTransform(float seconds, const aiAnimation& animation);

private:

    const aiNodeAnim& findChannel(std::string name, const aiAnimation& animation);

    glm::mat4 calcScalingMatrix(float animationTime, const aiNodeAnim& channel);
    glm::mat4 calcRotationMatrix(float animationTime, const aiNodeAnim& channel);
    glm::mat4 calcTranslationMatrix(float animationTime, const aiNodeAnim& channel);

    uint findPosition(float animationTime, const aiNodeAnim& channel);
    uint findRotation(float animationTime, const aiNodeAnim& channel);
    uint findScaling(float AnimationTime, const aiNodeAnim& channel);

    aiVector3D calcInterpolatedPosition(float AnimationTime, const aiNodeAnim& channel);
    aiQuaternion calcInterpolatedRotation(float AnimationTime, const aiNodeAnim& channel);
    aiVector3D calcInterpolatedScaling(float animationTime, const aiNodeAnim& channel);


};

#endif // BONE_H
