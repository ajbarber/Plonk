#include "skeleton.h"

Skeleton::Skeleton(std::shared_ptr<aiScene> scene)
{
}

std::vector<Bone> Skeleton::getBones()
{
    return this->bones;
}


