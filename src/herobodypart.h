#ifndef HEROBODY_H
#define HEROBODY_H

#include "drawing.h"
#include <assimp/scene.h>
#include "bones.h"
#include <glm/glm.hpp>
#include <memory>


class HeroBodyPart : public Drawing
{
public:
    HeroBodyPart(const aiScene& scene, const aiMesh& mesh, std::string textureFileName);
    ~HeroBodyPart() {}
    glm::mat4 getTransform(int index, float seconds);

private:
    void load(const aiMesh& mesh, std::string textureFileName);
    std::unique_ptr<Bones> bones;
    void makeSkeleton(const aiScene& scene, const aiMesh& mesh);



};

#endif // HEROBODY_H
