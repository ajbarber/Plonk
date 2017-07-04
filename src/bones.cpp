#include "bones.h"
#include <unordered_map>
#include <memory>
#include <string>

Bones::Bones(Bones *rhs) : bones(rhs->bones) {}

Bones::Bones(const aiMesh& aiMesh, const aiNode& aiNode)
{
    int err = Bones::load(aiMesh, aiNode);
}

list<shared_ptr<Bone>> Bones::getBones(int index) {
    return bones[index];
}

/*
 * Create vector of Bone indexed by
 * vertex id
 */
int Bones::load(const aiMesh& aimesh, const aiNode& ainode)
{   
    unordered_map<string, const shared_ptr<Bone>> boneMap;

    for (int idx = 0; idx < aimesh.mNumBones; idx++)
    {
        auto bone = make_shared<Bone>(new Bone());

        const aiBone& aibone = *aimesh.mBones[idx];
        const aiNode *node = ainode.FindNode(aibone.mName); //walk nodes

        bone->worldToBone = toglm(aibone.mOffsetMatrix);
        bone->boneToParent = toglm(node->mTransformation);
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

    bones = std::vector<list<shared_ptr<Bone>>>(aimesh.mNumVertices);

    for (int idx = 0; idx < aimesh.mNumBones; idx++)
    {
        const aiBone& aibone = *aimesh.mBones[idx];
        std::string name(aibone.mName.C_Str());
        auto bone = boneMap[name];
        bone->parent = boneMap[bone->parentName];

        for (int j = 0; j < aibone.mNumWeights; j++)
        {
            aiVertexWeight curWeight = aibone.mWeights[j];
            bone->weight = aibone.mWeights[j].mWeight;
            bones[curWeight.mVertexId].push_back(bone);
        }

    }

    return 0;

}





