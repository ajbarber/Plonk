#include "bones.h"
#include <unordered_map>
#include <memory>
#include <string>

Bones::Bones(Bones *rhs) : bones(rhs->bones) {}

Bones::Bones(const aiMesh& aiMesh, const aiNode& aiNode) :
    bones(vector<shared_ptr<Bone>>(aiMesh.mNumBones)),
    blendWeights(vector<glm::vec4>(aiMesh.mNumVertices, glm::vec4{0,0,0,0})),
    blendIndices(vector<glm::vec4>(aiMesh.mNumVertices, glm::vec4{0,0,0,0}))
{
    int err = Bones::load(aiMesh, aiNode);
}

std::vector<glm::mat4> Bones::getTransform(float seconds, const aiAnimation& animation) {
    std::vector<glm::mat4> transforms;// = std::vector<glm::mat4>(bones.size());
    for (auto& bone: bones) {
         transforms.push_back(bone->worldToBone * bone->getTransform(seconds, animation));
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
int Bones::load(const aiMesh& aimesh, const aiNode& ainode)
{   
    unordered_map<string, const shared_ptr<Bone>> boneMap;    
    aiNode& node = const_cast<aiNode&>(ainode);
    glm::mat4 inverseGlobal = toglm(node.mTransformation.Inverse());

    for (int idx = 0; idx < aimesh.mNumBones; idx++)
    {
        auto bone = make_shared<Bone>();

        const aiBone& aibone = *aimesh.mBones[idx];
        const aiNode *node = ainode.FindNode(aibone.mName); //walk nodes

        bone->worldToBone = toglm(aibone.mOffsetMatrix);
        bone->boneToParent = toglm(node->mTransformation);
        bone->inverseGlobal = inverseGlobal;
        std::string name(aibone.mName.C_Str());
        bone->name = name;

        assert(!bone->name.empty());

        if (node->mParent != nullptr)
        {
            std::string parentName(node->mParent->mName.C_Str());
            bone->parentName = parentName;
        }

        boneMap.insert({bone->name, bone });

    }

    for (int idx = 0; idx < aimesh.mNumBones; idx++)
    {
        const aiBone& aibone = *aimesh.mBones[idx];
        string name(aibone.mName.C_Str());
        auto bone = boneMap[name];
        bone->parent = boneMap[bone->parentName];
        bones[idx]=bone;



        for (int j = 0; j < aibone.mNumWeights; j++)
        {
            aiVertexWeight curWeight = aibone.mWeights[j];

            auto i = curWeight.mVertexId;

            if (blendWeights[i].x == 0)
            {
                blendWeights[i].x = curWeight.mWeight;
                blendIndices[i].x = idx;
            }
            else if (blendWeights[i].y == 0)
            {
                blendWeights[i].y = curWeight.mWeight;
                blendIndices[i].y = idx;
            }
            else if (blendWeights[i].z == 0) {
                blendWeights[i].z = curWeight.mWeight;
                blendIndices[i].z = idx;
            }
            else if (blendWeights[i].w == 0) {
                blendWeights[i].w = curWeight.mWeight;
                blendIndices[i].w = idx;
            }
        }

    }

    return 0;

}





