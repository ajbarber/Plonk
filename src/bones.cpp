#include "bones.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

Bones::Bones(Bones *rhs) : bones(rhs->bones) {}

Bones::Bones(const aiScene& scene, const aiMesh& aiMesh) :
    bones(vector<shared_ptr<Bone>>(aiMesh.mNumBones)),
    blendWeights(vector<glm::vec4>(aiMesh.mNumVertices, glm::vec4{0,0,0,0})),
    blendIndices(vector<glm::vec4>(aiMesh.mNumVertices, glm::vec4{-1,-1,-1,-1}))
{
    Bones::load(scene, aiMesh);
}

std::vector<glm::mat4> Bones::getTransform(float seconds,
                                           const aiNode& node,
                                           const aiAnimation& animation)
{
    std::vector<glm::mat4> transforms;// = std::vector<glm::mat4>(bones.size());
    auto global = node.mTransformation;

    auto inverse = glm::inverse(toglm(global));
    propagateNodes(node, animation, glm::mat4(1.0), inverse, seconds);

    for (auto& bone: bones) {
        transforms.push_back(bone->inverseGlobal *
                             bone->transform * bone->worldToBone) ;
    }

    return transforms;
}

std::vector<glm::vec4> Bones::getBlendWeights() {
    return blendWeights;
}

std::vector<glm::vec4> Bones::getBlendIndices() {
    return blendIndices;
}

/*
 * Create vector of Bone indexed by
 * vertex id
 */
void Bones::makeBonesMap(const aiScene& aiScene)
{
    for (std::size_t i = 0; i < aiScene.mNumMeshes; i++)
    {
        const aiMesh* aimesh = aiScene.mMeshes[i];
        for (std::size_t j = 0; j < aimesh->mNumBones; j++)
        {
            auto bone = make_shared<Bone>();
            const aiBone& aibone = *aimesh->mBones[j];

            bone->worldToBone = toglm(aibone.mOffsetMatrix);
            std::string name(aibone.mName.data);
            bone->name = name;
            boneMap.insert({bone->name, bone });
        }
    }
}

void Bones::propagateNodes(const aiNode& ainode,
                           const aiAnimation& aiAnim,
                           glm::mat4 parentTransform,
                           glm::mat4 inverseGlobal,
                           float seconds)
{

    glm::mat4 nodeTransform = parentTransform * toglm(ainode.mTransformation);
    std::string nodeName(ainode.mName.data);

    if (boneMap.find(nodeName) != boneMap.end())
    {
        auto& bone = boneMap[nodeName];

        bone->updateTransform(seconds, aiAnim, parentTransform, nodeTransform);
        nodeTransform = bone->transform;

        if (ainode.mParent)
        {
            std::string parentName(ainode.mParent->mName.data);
            bone->parentName = parentName;
        }
        bone->inverseGlobal = inverseGlobal;
    }

    for (std::size_t i = 0; i < ainode.mNumChildren; i++ )
    {
        const aiNode* child = ainode.mChildren[i];
        propagateNodes(*child, aiAnim, nodeTransform, inverseGlobal, seconds);
    }
}

void Bones::load(const aiScene& aiscene, const aiMesh& aimesh)
{
    makeBonesMap(aiscene);

    for (std::size_t idx = 0; idx < aimesh.mNumBones; idx++)
    {
        const aiBone& aibone = *aimesh.mBones[idx];
        string name(aibone.mName.data);
        auto bone = boneMap[name];
        bone->parent = boneMap[bone->parentName];
        bones[idx]=bone;

        for (std::size_t j = 0; j < aibone.mNumWeights; j++)
        {
            aiVertexWeight curWeight = aibone.mWeights[j];

            auto i = curWeight.mVertexId;

            if (blendIndices[i].x == -1)
            {
                blendWeights[i].x = curWeight.mWeight;
                blendIndices[i].x = idx;
            }
            else if (blendIndices[i].y == -1)
            {
                blendWeights[i].y = curWeight.mWeight;
                blendIndices[i].y = idx;
            }
            else if (blendIndices[i].z == -1) {
                blendWeights[i].z = curWeight.mWeight;
                blendIndices[i].z = idx;
            }
            else if (blendIndices[i].w == -1) {
                blendWeights[i].w = 1.0-blendWeights[i].z-
                    blendWeights[i].y-blendWeights[i].x;
                blendIndices[i].w = idx;
            }
        }
    }
}
