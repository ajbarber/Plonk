#include "hero.h"
#include "bones.h"

Hero::Hero(const aiScene& scene)
{
    fillData(scene);
}

vector<unique_ptr<HeroBodyPart>>& Hero::getBodyParts()
{
    return bodyParts;
}

void Hero::fillData(const aiScene& scene)
{
    vector<const aiMesh*> meshes;
    vector<string> textureFileNames;

    if (scene.HasMeshes())
    {
        for (uint idx=0; idx < scene.mNumMeshes; idx++)
        {
            const aiMesh* mesh = scene.mMeshes[idx];
            uint matIdx = mesh->mMaterialIndex;
            meshes.push_back(mesh);
            std::string texFileName(getMaterial(scene, matIdx));
            if (!texFileName.empty())
                textureFileNames.push_back(texFileName);
        }
    }

    for (std::size_t idx = 0; idx < meshes.size(); idx++)
    {
        bodyParts.push_back(make_unique<HeroBodyPart>(scene, *meshes[idx], textureFileNames[idx]));
    }
}

std::string Hero::getMaterial(const aiScene& scene, int idx)
{
    string res;
    if (scene.HasMaterials())
    {
        const aiMaterial& mat = *scene.mMaterials[idx];

        if (mat.GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString path;

            if (mat.GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
               string p(path.data);
               res = p;
           }
       }
    }
    return res;
}

