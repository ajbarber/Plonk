#ifndef BONES_H
#define BONES_H

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "structs.h"
#include "util.h"
#include <vector>
#include <map>

class Bones
{
public:
    Bones() {}
    Bones(const aiMesh& aiMesh, const aiNode& aiNode);

private:
    int load(const aiMesh& aiMesh,  const aiNode& aiNode);

    std::vector<Bone> bones;
    std::vector<float> weights;
};

#endif // BONES_H
