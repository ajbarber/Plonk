#include "bone.h"
#include "util.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Bone::Bone(Bone* bone): name(bone->name), parentName(bone->parentName),
                        boneToParent(bone->boneToParent), worldToBone(bone->worldToBone),
                        inverseGlobal(bone->inverseGlobal), parent(bone->parent) {}

 glm::mat4 Bone::getTransform(float seconds, const aiAnimation& animation)
 {
     //return glm::mat4(1.0f);

     float ticksPerSecond = animation.mTicksPerSecond != 0 ?
                             animation.mTicksPerSecond : 25.0f;
     float ticks = seconds * ticksPerSecond;
     float animationTime = fmod(ticks, animation.mDuration);

     if (name.empty())
        return glm::mat4(1.0f);

     const aiNodeAnim& channel = findChannel(name, animation);

     auto scale = calcScalingMatrix(animationTime, channel);
     auto rotate = calcRotationMatrix(animationTime, channel);
     auto translate = calcTranslationMatrix(animationTime, channel);
     
     //return glm::translate(glm::mat4(1), glm::vec3(100,1,0));
     auto currentTx = translate * rotate * scale ;
     auto parentTx = (parent == nullptr) ? inverseGlobal : parent->getTransform(animationTime, animation);
     return parentTx * currentTx;
 }

 const aiNodeAnim& Bone::findChannel(std::string name, const aiAnimation& animation)
 {
     for (auto i = 0 ; i < animation.mNumChannels; i++)
     {
         if (name.compare(animation.mChannels[i]->mNodeName.C_Str())==0)
         {
             return *animation.mChannels[i];
         }
     }
     assert(false);
 }

 glm::mat4 Bone::calcScalingMatrix(float animationTime, const aiNodeAnim& channel)
 {
     aiVector3D scaling = calcInterpolatedScaling(animationTime, channel);
     return toscalingmat(scaling);
 }

 glm::mat4 Bone::calcRotationMatrix(float animationTime, const aiNodeAnim& channel)
 {
     aiQuaternion rotation = calcInterpolatedRotation(animationTime, channel);
     return torotationmat(rotation.GetMatrix());
 }

 glm::mat4 Bone::calcTranslationMatrix(float animationTime, const aiNodeAnim& channel)
 {
     aiVector3D translation = calcInterpolatedPosition(animationTime, channel);
     return totranslationmat(translation);
 }

 uint Bone::findPosition(float animationTime, const aiNodeAnim& channel)
 {
     for (uint i = 0 ; i < channel.mNumPositionKeys - 1 ; i++) {
         if (animationTime < (float)channel.mPositionKeys[i + 1].mTime) {
             return i;
         }
     }

     assert(0);

     return 0;
 }

 uint Bone::findRotation(float animationTime, const aiNodeAnim& channel)
 {
     assert(channel.mNumRotationKeys > 0);

     for (uint i = 0 ; i < channel.mNumRotationKeys - 1 ; i++) {
         if (animationTime < (float)channel.mRotationKeys[i + 1].mTime) {
             return i;
         }
     }

     assert(0);

     return 0;
 }

 uint Bone::findScaling(float animationTime, const aiNodeAnim& channel)
 {
     assert(channel.mNumScalingKeys > 0);

     for (uint i = 0 ; i < channel.mNumScalingKeys - 1 ; i++) {
         if (animationTime < (float)channel.mScalingKeys[i + 1].mTime) {
             return i;
         }
     }

     assert(0);

     return 0;
 }

 aiVector3D Bone::calcInterpolatedPosition(float animationTime, const aiNodeAnim& channel)
 {
     aiVector3D res;
     if (channel.mNumPositionKeys == 1) {
         res = channel.mPositionKeys[0].mValue;
         return res;
     }

     uint positionIndex = findPosition(animationTime, channel);
     uint nextPositionIndex = (positionIndex + 1);
     assert(nextPositionIndex < channel.mNumPositionKeys);
     float deltaTime = (float)(channel.mPositionKeys[nextPositionIndex].mTime - channel.mPositionKeys[positionIndex].mTime);
     float factor = (animationTime - (float)channel.mPositionKeys[positionIndex].mTime) / deltaTime;
     assert(factor >= 0.0f && factor <= 1.0f);
     const aiVector3D& start = channel.mPositionKeys[positionIndex].mValue;
     const aiVector3D& end = channel.mPositionKeys[nextPositionIndex].mValue;
     aiVector3D delta = end - start;
     res = start + factor * delta;
     return res;
 }

 aiQuaternion Bone::calcInterpolatedRotation(float animationTime, const aiNodeAnim& channel)
 {
     aiQuaternion res;
     // we need at least two values to interpolate...
     if (channel.mNumRotationKeys == 1) {
         res = channel.mRotationKeys[0].mValue;
         return res;
     }

     uint rotationIndex = findRotation(animationTime, channel);
     uint nextRotationIndex = (rotationIndex + 1);
     assert(nextRotationIndex < channel.mNumRotationKeys);
     float deltaTime = channel.mRotationKeys[nextRotationIndex].mTime - channel.mRotationKeys[rotationIndex].mTime;
     float factor = (animationTime - (float)channel.mRotationKeys[rotationIndex].mTime) / deltaTime;
     assert(factor >= 0.0f && factor <= 1.0f);
     const aiQuaternion& startRotationQ = channel.mRotationKeys[rotationIndex].mValue;
     const aiQuaternion& endRotationQ = channel.mRotationKeys[nextRotationIndex].mValue;

     aiQuaternion::Interpolate(res, startRotationQ, endRotationQ, factor);
     res = res.Normalize();
     return res;
 }

 aiVector3D Bone::calcInterpolatedScaling(float animationTime, const aiNodeAnim& channel)
 {
     aiVector3D res;
     if (channel.mNumScalingKeys == 1) {
         res = channel.mScalingKeys[0].mValue;
         return res;
     }

     uint scalingIndex = findScaling(animationTime, channel);
     uint nextScalingIndex = (scalingIndex + 1);
     assert(nextScalingIndex < channel.mNumScalingKeys);
     float deltaTime = (float)(channel.mScalingKeys[nextScalingIndex].mTime - channel.mScalingKeys[scalingIndex].mTime);
     float factor = (animationTime - (float)channel.mScalingKeys[scalingIndex].mTime) / deltaTime;
     assert(factor >= 0.0f && factor <= 1.0f);
     const aiVector3D& start = channel.mScalingKeys[scalingIndex].mValue;
     const aiVector3D& end   = channel.mScalingKeys[nextScalingIndex].mValue;
     aiVector3D delta = end - start;
     res = start + factor * delta;
 }

