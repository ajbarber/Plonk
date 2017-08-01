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
#include <unordered_map>
#include <memory>


using namespace std;


class Bones
{

public:

    Bones(Bones* bones);
    Bones(const aiScene& scene, const aiMesh& aiMesh);
    std::vector<glm::mat4> getTransform(float seconds, const aiNode& node,
    const aiAnimation& animation);
    std::vector<glm::vec4> getBlendWeights();
    std::vector<glm::vec4> getBlendIndices();

private:
    
    int load(const aiScene& scene, const aiMesh& aiMesh);
    void makeBonesMap(const aiScene& aiscene);
    void propagateNodes(const aiNode& ainode,
                           const aiAnimation& aiAnim,
                           glm::mat4 parentTransform,
                           glm::mat4 inverseGlobal,
                           float seconds);
    std::vector<glm::vec4> blendWeights;
    std::vector<glm::vec4> blendIndices;

    //each vertices list of composing bones
    vector<shared_ptr<Bone>> bones;

    unordered_map<string, const shared_ptr<Bone>> boneMap; 


};

#endif // BONES_H
