#ifndef BONES_H
#define BONES_H

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "structs.h"
#include "util.h"
#include <vector>
#include <list>
#include "bone.h"

using namespace std;


class Bones
{
public:
    Bones() {}
    Bones(Bones* bones);
    Bones(const aiMesh& aiMesh, const aiNode& aiNode);
    list<shared_ptr<Bone>> getBones(int index);


private:
    int load(const aiMesh& aiMesh,  const aiNode& aiNode);

    //each vertices list of composing bones
    vector<list<shared_ptr<Bone>>> bones;


};

#endif // BONES_H
