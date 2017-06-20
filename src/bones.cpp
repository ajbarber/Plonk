#include "bones.h"

Bones::Bones(const aiMesh& aiMesh, const aiNode& aiNode)
{
    int err = Bones::load(aiMesh, aiNode);
}


/*
 * Create vector of Bone indexed by
 * vertex id
 *
 */
int Bones::load(const aiMesh& aimesh, const aiNode& ainode)
{
    bones=std::vector<Bone>(aimesh.mNumVertices);
    weights=std::vector<float>(aimesh.mNumVertices);
    for (int idx = 0; idx < aimesh.mNumBones; idx++)
    {
        const aiBone &aibone = *aimesh.mBones[idx];
        //aiString boneName = aibone.mName;

        //const std::string boneNameStr;
        Bone bone;

        bone.worldToBone=toglm(aibone.mOffsetMatrix);

        const aiNode* node = ainode.FindNode(aibone.mName);

        bone.boneToParent = toglm(node->mTransformation);

        //node->mParent;


        for (int j = 0; j < aibone.mNumWeights; j++)
        {
            aiVertexWeight curWeight = aibone.mWeights[j];
            bones[curWeight.mVertexId] = bone;
            weights[curWeight.mVertexId] = aibone.mWeights[j].mWeight;
        }


        //boneName.Set(boneNameStr);

        //bones[boneNameStr]= bone;

    }

    return 0;

}

