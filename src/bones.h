#ifndef BONES_H
#define BONES_H

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "structs.h"
#include "util.h"
#include <vector>
#include <list>
#include "bone.h"
#include <glm/glm.hpp>

using namespace std;


class Bones
{

public:

    Bones(Bones* bones);
    Bones(const aiMesh& aiMesh, const aiNode& aiNode);
    std::vector<glm::mat4> getTransform(float seconds, const aiAnimation& animation);
    std::vector<glm::vec4> getBlendWeights();
    std::vector<glm::vec4> getBlendIndices();

private:

    int load(const aiMesh& aiMesh,  const aiNode& aiNode);
    std::vector<glm::vec4> blendWeights;
    std::vector<glm::vec4> blendIndices;

    //each vertices list of composing bones
    vector<shared_ptr<Bone>> bones;


};

#endif // BONES_H
