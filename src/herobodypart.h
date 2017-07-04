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

    HeroBodyPart() {}
    HeroBodyPart(HeroBodyPart &&other);
    HeroBodyPart(const HeroBodyPart &other);
    HeroBodyPart& operator= (const HeroBodyPart& rhs) ;
    ~HeroBodyPart() {}
    HeroBodyPart(const aiScene& scene, const aiMesh& mesh, std::string textureFileName);   
    glm::mat4 getTransform(int index, float seconds);

private:
    void load(const aiMesh& mesh, std::string textureFileName);
    std::shared_ptr<aiAnimation> animation;
    std::shared_ptr<Bones> bones;
    void makeSkeleton(const aiScene& scene, const aiMesh& mesh);


};

#endif // HEROBODY_H
