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
    std::vector<glm::mat4> getTransforms(float seconds) const;
    std::shared_ptr<Bones> getSkeleton() const;

private:
    void load(const aiMesh& mesh, std::string textureFileName);
    std::unique_ptr<aiAnimation> animation;
    std::shared_ptr<Bones> bones;
    void makeSkeleton(const aiScene& scene, const aiMesh& mesh);
    glm::mat4 inverseGlobal;
};

#endif // HEROBODY_H
