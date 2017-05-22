#ifndef HERO_H
#define HERO_H

#include "drawing.h"
#include "bones.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Hero : public Drawing
{
public:
    Hero(const aiScene& scene);

private:
    void fillData(const aiScene& scene);
    Bones bones;
    aiNode* getBoneMapping(aiNode& node, const std::string id);
    void loadVertices(const aiMesh& mesh);

};

#endif // HERO_H
