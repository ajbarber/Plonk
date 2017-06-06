#include "hero.h"

Hero::Hero(const aiScene& scene)
{
    Hero::fillData(scene);

}

void Hero::fillData(const aiScene& scene)
{    

    if (scene.HasMeshes())
    {
        for (uint idx=0; idx< scene.mNumMeshes; idx++)
        {
            const aiMesh& mesh = *scene.mMeshes[idx];
            Bones *bones = new Bones(mesh, *scene.mRootNode);
            loadVertices(mesh);

        }
    }

}

aiNode* Hero::getBoneMapping(aiNode& node, const std::string id)
{
    return node.FindNode(aiString(id));
}

void Hero::loadVertices(const aiMesh& mesh)
{

    for (uint i = 0; i < mesh.mNumVertices; i++)
    {
        auto v = mesh.mVertices[i];
        auto n = mesh.mNormals[i];

        glm::vec3 pos(v.x, v.y, v.z);
        glm::vec3 normal(n.x, n.y, n.z);

        Vertex vert = Vertex { pos = pos, normal = normal };

        indices.push_back(i);
        vertices.push_back(vert);
    }

}



