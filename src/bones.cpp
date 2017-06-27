#include "bones.h"
#include <unordered_map>

Bones::Bones(const aiMesh& aiMesh, const aiNode& aiNode)
{
    int err = Bones::load(aiMesh, aiNode);
}

std::list<Bone> Bones::getBones(int index)
{
    return bones[index];
}

/*
 * Create vector of Bone indexed by
 * vertex id
 */
int Bones::load(const aiMesh& aimesh, const aiNode& ainode)
{
    bones=std::vector<std::list<Bone>>(aimesh.mNumVertices);
    std::unordered_map<std::string, Bone> boneMap;

    for (int idx = 0; idx < aimesh.mNumBones; idx++)
    {
        Bone bone;
        const aiBone& aibone = *aimesh.mBones[idx];
        const aiNode *node = ainode.FindNode(aibone.mName); //walk nodes

        bone.worldToBone = toglm(aibone.mOffsetMatrix);
        bone.boneToParent = toglm(node->mTransformation);
        bone.name = aibone.mName.C_Str();

        if (node->mParent != nullptr)
        {
            bone.parentName = node->mParent->mName.C_Str();
        }

        boneMap.insert({bone.name, bone});
    }

    for (int idx = 0; idx < aimesh.mNumBones; idx++)
    {
        const aiBone& aibone = *aimesh.mBones[idx];
        Bone bone = boneMap[aibone.mName.C_Str()];
        bone.parent = &boneMap[bone.parentName];

        for (int j = 0; j < aibone.mNumWeights; j++)
        {
            aiVertexWeight curWeight = aibone.mWeights[j];
            bone.weight = aibone.mWeights[j].mWeight;
            bones[curWeight.mVertexId].push_back(bone);
        }

    }

    return 0;

}





