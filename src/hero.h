#ifndef HERO_H
#define HERO_H

#include "drawing.h"
#include "bones.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Hero
{
public:
    Hero(const aiScene &scene);

private:
    void fillData(const aiScene &scene);
    Bones bones;
};

#endif // HERO_H
