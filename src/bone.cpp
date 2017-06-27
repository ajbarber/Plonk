#include "bone.h"

 glm::mat4 Bone::getTransform(float seconds, const aiAnimation& animation)
 {
     return worldToBone * boneToParent ;

     auto channel = findChannel(name, animation);

 }

 aiNodeAnim& findChannel(std::string name, const aiAnimation& animation)
 {
     for (auto i = 0 ; i < animation.mNumChannels; i++)
     {
         if (animation.mChannels[i]->mNodeName.C_Str() == name)
             return *animation.mChannels[i];
     }
 }

 aiQuaternion& Bone::calcInterpolatedRotation(float AnimationTime, const aiNodeAnim& channel)
 {
     // we need at least two values to interpolate...
     if (channel->mNumRotationKeys == 1) {
         Out = channel->mRotationKeys[0].mValue;
         return;
     }

     uint rotationIndex = findRotation(AnimationTime, channel);
     uint nextRotationIndex = (rotationIndex + 1);
     assert(nextRotationIndex < channel->mNumRotationKeys);
     float deltaTime = channel.mRotationKeys[nextRotationIndex].mTime - channel.mRotationKeys[rotationIndex].mTime;
     float factor = (animationTime - (float)channel.mRotationKeys[rotationIndex].mTime) / deltaTime;
     assert(factor >= 0.0f && factor <= 1.0f);
     const aiQuaternion& startRotationQ = channel.mRotationKeys[rotationIndex].mValue;
     const aiQuaternion& endRotationQ = channel.mRotationKeys[nextRotationIndex].mValue;

     aiQuaternion::Interpolate(Out, startRotationQ, endRotationQ, factor);
     Out = Out.Normalize();
 }
