#include "bones.h"

Bones::Bones(const aiMesh& aiMesh)
{
    int err = Bones::load(aiMesh);
}

int Bones::load(const aiMesh& aiMesh)
{
    for (int idx = 0; idx < aiMesh.mNumBones; idx++)
    {
        const aiBone &aibone = *aiMesh.mBones[idx];
        aiString boneName = aibone.mName;

        const std::string boneNameStr;
        Bone bone;

        bone.relativeXForm=toglm(aibone.mOffsetMatrix);
        boneName.Set(boneNameStr);

        boneMap[boneNameStr]= bone;

    }

    return 0;

}

