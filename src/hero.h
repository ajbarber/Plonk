#ifndef HERO_H
#define HERO_H

#include "herobodypart.h"
#include <vector>

using namespace std;

class Hero
{
public:
    Hero(const aiScene& scene);
    vector<unique_ptr<HeroBodyPart>>& getBodyParts();
    ~Hero() {}


private:
    vector<unique_ptr<HeroBodyPart>> bodyParts;
    string getMaterial(const aiScene& scene, int idx);
    void fillData(const aiScene& scene);
};

#endif // HERO_H
