#include "util.h"

glm::mat4 toglm(const aiMatrix4x4& in_mat)
{
    glm::mat4 tmp;
    
    tmp[0][0] = in_mat[0][0];
    tmp[0][1] = in_mat[1][0];
    tmp[0][2] = in_mat[2][0];
    tmp[0][3] = in_mat[3][0];

    tmp[1][0] = in_mat[0][1];
    tmp[1][1] = in_mat[1][1];
    tmp[1][2] = in_mat[2][1];
    tmp[1][3] = in_mat[3][1];

    tmp[2][0] = in_mat[0][2];
    tmp[2][1] = in_mat[1][2];
    tmp[2][2] = in_mat[2][2];
    tmp[2][3] = in_mat[3][2];

    tmp[3][0] = in_mat[0][3];
    tmp[3][1] = in_mat[1][3];
    tmp[3][2] = in_mat[2][3];
    tmp[3][3] = in_mat[3][3];
    return tmp;
}

glm::mat4 toscalingmat(const aiVector3D& vec)
{
    glm::vec3 scaling(vec.x, vec.y, vec.z);
    return glm::scale(glm::mat4(1.0f), scaling);
}


glm::mat4 totranslationmat(const aiVector3D& vec)
{
    glm::vec3 translation(vec.x, vec.y, vec.z);
    return glm::translate(glm::mat4(1.0f), translation);
}

glm::mat4 torotationmat(aiQuaternion& quart)
{
    glm::quat rotation(quart.w, quart.x, quart.y, quart.z);

    return glm::mat4_cast(rotation);
}