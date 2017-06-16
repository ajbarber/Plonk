#ifndef HEROBODY_H
#define HEROBODY_H

#include "drawing.h"
#include <assimp/scene.h>
#include "bones.h"


class HeroBodyPart : public Drawing
{
public:
    HeroBodyPart(const aiMesh& mesh, std::string textureFileName);
    ~HeroBodyPart() {}

private:
    void load(const aiMesh& mesh, std::string textureFileName);
    Bones bones;
    aiNode* getBoneMapping(aiNode& node, const std::string id);



};

#endif // HEROBODY_H
