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
    Bones(const aiMesh& aiMesh);

private:
    int load(const aiMesh& aiMesh);

    std::vector<Bone> bones;
    std::map<std::string, Bone> boneMap;
};

#endif // BONES_H
