#ifndef UTIL
#define UTIL

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> 

glm::mat4 toglm(const aiMatrix4x4& in_mat);

glm::mat4 toglmold(const aiMatrix4x4& in_mat);

glm::mat4 toscalingmat(const aiVector3D& vec);

glm::mat4 totranslationmat(const aiVector3D& vec);

glm::mat4 torotationmat(aiQuaternion& quart);


#endif // UTIL

