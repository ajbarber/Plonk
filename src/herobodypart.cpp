#include "herobodypart.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <list>
#include "soilfactory.h"
#include "structs.h"


HeroBodyPart::HeroBodyPart(const aiScene& scene, const aiMesh& mesh, std::string textureFileName)
{
    load(mesh, textureFileName);
    makeSkeleton(scene, mesh);
}


void HeroBodyPart::load(const aiMesh& mesh, std::string textureFileName)
{
    for (uint i = 0; i < mesh.mNumVertices; i++)
    {
        auto v = mesh.mVertices[i];
        auto n = mesh.mNormals[i];

        const aiVector3D zero(0.0f, 0.0f, 0.0f);
        const aiVector3D& texCoord = mesh.HasTextureCoords(0) ? mesh.mTextureCoords[0][i] : zero;

        glm::vec3 pos(v.x, v.y, v.z);
        glm::vec3 normal(n.x, n.y, n.z);
        glm::vec2 tex(texCoord.x, texCoord.y);


        Vertex vert = Vertex { pos = pos,
                               normal = normal,
                               tex = tex};

        vertices.push_back(vert);

    }

    //texture = nullptr;
    this->texture = SoilFactory::load(textureFileName);
    fprintf(stderr, "Loaded texture of %d", *this->texture);

    for (uint i = 0; i < mesh.mNumFaces; i++)
    {
        const aiFace& face = mesh.mFaces[i];
        assert(face.mNumIndices == 3);

        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

}

/*
 * Return array o
 *
 * */
void HeroBodyPart::makeSkeleton(const aiScene& scene, const aiMesh& mesh)
{
    bones = std::unique_ptr<Bones>(new Bones(mesh, *scene.mRootNode));
}

glm::mat4 HeroBodyPart::getTransform(int index, float seconds)
{
    auto bonesList = bones->getBones(index);
    for (auto &bone: bonesList)
    {
        bone.worldToBone * bone.boneToParent;

    }


}







