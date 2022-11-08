#include "bone.h"
#include "util.h"
#include <string>
#include <glm/glm.hpp>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

Bone::Bone(Bone* bone): name(bone->name), parentName(bone->parentName),
                        transform(bone->transform), worldToBone(bone->worldToBone),
                        inverseGlobal(bone->inverseGlobal), parent(bone->parent) {}

void Bone::updateTransform(float seconds,
                           const aiAnimation& animation,
                           glm::mat4 parentTransform,
                           glm::mat4 defaultTransform)
{
    float ticksPerSecond = animation.mTicksPerSecond != 0 ?
        animation.mTicksPerSecond : 25.0f;
    float ticks = seconds * ticksPerSecond;
    float animationTime = fmod(ticks, animation.mDuration);

    if (name.empty())
        assert(false);

    const aiNodeAnim* channel = findChannel(name, &animation);

    glm::mat4 currentTx = glm::mat4(1.0);
    if (channel)
    {
        auto scale = calcScalingMatrix(animationTime, *channel);
        auto rotate = calcRotationMatrix(animationTime, *channel);
        auto translate = calcTranslationMatrix(animationTime, *channel);

        currentTx =  parentTransform * translate * rotate * scale ; // translate * rotate * scale ;
    }
    else
    {
        currentTx = defaultTransform;
    }

    this->transform = currentTx;

}

const aiNodeAnim* Bone::findChannel(const std::string name, const aiAnimation* animation)
{
    for (std::size_t i = 0 ; i < animation->mNumChannels; i++)
    {
        const aiNodeAnim* node = animation->mChannels[i];
        if (std::string(node->mNodeName.data) == name)
        {
            return node;
        }
    }
    assert(false);
}

int Bone::getStartKey(float animationTime)
{
    int key1;
    if (std::round(animationTime) < animationTime)
    {
        key1 = std::round(animationTime);
    }
    else
    {
        key1 = std::round(animationTime) - 1;
    }

    return key1;
}

aiVector3D Bone::calcInterpolatedPosition(float animationTime, const aiNodeAnim& channel)
{
    aiVector3D aiTranslation(channel.mPositionKeys[0].mValue);

    Assimp::Interpolator<aiVector3D> lerp;

    int key1 = getStartKey(animationTime);
    int key2 = key1 + 1;

    if (channel.mNumPositionKeys > 1)
    {
        lerp(aiTranslation, channel.mPositionKeys[key1].mValue,
             channel.mPositionKeys[key2].mValue, animationTime - key1);
    }

    return aiTranslation;

}

aiQuaternion Bone::calcInterpolatedRotation(float animationTime, const aiNodeAnim& channel)
{
    aiQuaternion res(channel.mRotationKeys[0].mValue);

    Assimp::Interpolator<aiQuaternion> slerp;

    int key1 = getStartKey(animationTime);
    int key2 = key1 + 1;

    if (channel.mNumRotationKeys > 1)
    {
        slerp(res,channel.mRotationKeys[key1].mValue, channel.mRotationKeys[key2].mValue, animationTime - key1);
    }

    return res;

}

aiVector3D Bone::calcInterpolatedScaling(float animationTime, const aiNodeAnim& channel)
{
    aiVector3D res(channel.mScalingKeys[0].mValue);

    Assimp::Interpolator<aiVector3D> lerp;

    int key1 = getStartKey(animationTime);
    int key2 = key1 + 1;

    if (channel.mNumScalingKeys > 1)
    {
        lerp(res, channel.mScalingKeys[key1].mValue,
             channel.mScalingKeys[key2].mValue, animationTime - key1);
    }

    return res;
}

glm::mat4 Bone::calcScalingMatrix(float animationTime, const aiNodeAnim& channel)
{
    aiVector3D scaling = calcInterpolatedScaling(animationTime, channel);
    return toscalingmat(scaling);
}

glm::mat4 Bone::calcRotationMatrix(float animationTime, const aiNodeAnim& channel)
{
    aiQuaternion rotation = calcInterpolatedRotation(animationTime, channel);
    return torotationmat(rotation);
}

glm::mat4 Bone::calcTranslationMatrix(float animationTime, const aiNodeAnim& channel)
{
    aiVector3D translation = calcInterpolatedPosition(animationTime, channel);
    return totranslationmat(translation);
}
