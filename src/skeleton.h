#ifndef SKELETON_H
#define SKELETON_H

#include "bones.h"
#include <vector>
#include <memory>

class Skeleton
{
public:
    Skeleton(std::shared_ptr<aiScene> scene);
    std::vector<Bone> getBones();

private:
    std::vector<Bone> bones;

};

#endif // SKELETON_H
