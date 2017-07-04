#ifndef UTIL
#define UTIL

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

static glm::mat4 toglm(const aiMatrix4x4& in_mat)
{
    glm::mat4 tmp;
    tmp[0][0] = in_mat.a1;
    tmp[1][0] = in_mat.b1;
    tmp[2][0] = in_mat.c1;
    tmp[3][0] = in_mat.d1;

    tmp[0][1] = in_mat.a2;
    tmp[1][1] = in_mat.b2;
    tmp[2][1] = in_mat.c2;
    tmp[3][1] = in_mat.d2;

    tmp[0][2] = in_mat.a3;
    tmp[1][2] = in_mat.b3;
    tmp[2][2] = in_mat.c3;
    tmp[3][2] = in_mat.d3;

    tmp[0][3] = in_mat.a4;
    tmp[1][3] = in_mat.b4;
    tmp[2][3] = in_mat.c4;
    tmp[3][3] = in_mat.d4;
    return tmp;
}

static glm::mat4 toscalingmat(const aiVector3D& vec)
{
    glm::mat4 tmp;
    tmp[0][0] = vec.x; tmp[0][1] = 0.0f;   tmp[0][2] = 0.0f;   tmp[0][3] = 0.0f;
    tmp[1][0] = 0.0f;  tmp[1][1] = vec.y;  tmp[1][2] = 0.0f;   tmp[1][3] = 0.0f;
    tmp[2][0] = 0.0f;  tmp[2][1] = 0.0f;   tmp[2][2] = vec.z;  tmp[2][3] = 0.0f;
    tmp[3][0] = 0.0f;  tmp[3][1] = 0.0f;   tmp[3][2] = 0.0f;   tmp[3][3] = 1.0f;
    return tmp;
}


static glm::mat4 totranslationmat(const aiVector3D& vec)
{
    glm::mat4 tmp;
    tmp[0][0] = 1.0f; tmp[0][1] = 0.0f; tmp[0][2] = 0.0f; tmp[0][3] = vec.x;
    tmp[1][0] = 0.0f; tmp[1][1] = 1.0f; tmp[1][2] = 0.0f; tmp[1][3] = vec.y;
    tmp[2][0] = 0.0f; tmp[2][1] = 0.0f; tmp[2][2] = 1.0f; tmp[2][3] = vec.z;
    tmp[3][0] = 0.0f; tmp[3][1] = 0.0f; tmp[3][2] = 0.0f; tmp[3][3] = 1.0f;
    return tmp;
}

static glm::mat4 torotationmat(const aiMatrix3x3& mat)
{
    glm::mat4 tmp;
    tmp[0][0] = mat.a1; tmp[0][1] = mat.a2; tmp[0][2] = mat.a3; tmp[0][3] = 0.0f;
    tmp[1][0] = mat.b1; tmp[1][1] = mat.b2; tmp[1][2] = mat.b3; tmp[1][3] = 0.0f;
    tmp[2][0] = mat.c1; tmp[2][1] = mat.c2; tmp[2][2] = mat.c3; tmp[2][3] = 0.0f;
    tmp[3][0] = 0.0f; tmp[3][1] = 0.0f; tmp[3][2] = 0.0f; tmp[3][3] = 1.0f;

    return tmp;
}

#endif // UTIL

