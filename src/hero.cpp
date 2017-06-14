#include "hero.h"
#include "bones.h"

Hero::Hero(std::shared_ptr<aiScene> scene)
{
    fillData(scene);
}

std::vector<std::shared_ptr<HeroBodyPart>> Hero::getBodyParts()
{
    return bodyParts;
}

void Hero::fillData(std::shared_ptr<aiScene> scene)
{
    std::vector<aiMesh*> meshes;
    std::vector<std::string> textureFileNames;

    if (scene->HasMeshes())
    {
        for (uint idx=0; idx < scene->mNumMeshes; idx++)
        {
            aiMesh* mesh = scene->mMeshes[idx];
            //Bones *bones = new Bones(mesh, *scene.mRootNode);
            uint matIdx = mesh->mMaterialIndex;
            meshes.push_back(mesh);
            textureFileNames.push_back(getMaterial(scene, matIdx));
        }
    }

    for (auto idx = 0; idx < meshes.size(); idx++)
    {
        HeroBodyPart* hbp = new HeroBodyPart(*meshes[idx], textureFileNames[idx]);
        std::shared_ptr<HeroBodyPart> hbp_sp(hbp);
        bodyParts.push_back(hbp_sp);
    }
}

std::string Hero::getMaterial(std::shared_ptr<aiScene> scene, int idx)
{
    std::string res;
    if (scene->HasMaterials())
    {
        const aiMaterial& mat = *scene->mMaterials[idx];

        if (mat.GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString path;

            if (mat.GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
               std::string p(path.data);
               res = p;

           }
       }
    }
    return res;
}

