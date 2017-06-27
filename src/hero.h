#ifndef HERO_H
#define HERO_H

#include "herobodypart.h"
#include <vector>

class Hero
{
public:
    Hero(std::shared_ptr<aiScene> scene);
    std::vector<std::shared_ptr<HeroBodyPart>> getBodyParts();
    ~Hero() {}


private:
    std::vector<std::shared_ptr<HeroBodyPart>> bodyParts;
    std::string getMaterial(std::shared_ptr<aiScene> scene, int idx);
    void fillData(std::shared_ptr<aiScene> scene);
};

#endif // HERO_H
