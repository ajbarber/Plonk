#include "hero.h"

Hero::Hero(const aiScene &scene)
{
    Hero::fillData(scene);

}

void Hero::fillData(const aiScene &scene)
{
    if (scene.HasMeshes())
    {
        for (uint idx=0; idx< scene.mNumMeshes; idx++)
        {
            const aiMesh &mesh = *scene.mMeshes[idx];
            Bones *bones = new Bones(mesh);

        }
    }

}



