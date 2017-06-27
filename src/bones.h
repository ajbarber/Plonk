#ifndef BONES_H
#define BONES_H

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "structs.h"
#include "util.h"
#include <vector>
#include <list>
#include "bone.h"


class Bones
{
public:
    Bones() {}
    Bones(const aiMesh& aiMesh, const aiNode& aiNode);

    std::list<Bone> getBones(int index);

private:
    int load(const aiMesh& aiMesh,  const aiNode& aiNode);

    std::vector<std::list<Bone>> bones;


};

#endif // BONES_H
