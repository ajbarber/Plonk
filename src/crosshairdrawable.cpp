#include "crosshairdrawable.h"

CrossHairDrawable::CrossHairDrawable(const Drawing& drawing): GLDrawable(drawing)
{

}

int CrossHairDrawable::bind()
{
    GLuint lightVerticesVBO;

    //setup light gizmo vertex array and buffer object
    glGenVertexArrays(1, &vaoID);

    std::vector<glm::vec3> points = drawing.getPoints();

    glGenBuffers(1, &lightVerticesVBO);
    glBindVertexArray(vaoID);

    glBindBuffer (GL_ARRAY_BUFFER, lightVerticesVBO);
    //pass light crosshair gizmo vertices to buffer object
    glBufferData (GL_ARRAY_BUFFER, points.size()*sizeof(glm::vec3), &(points[0].x), GL_STATIC_DRAW);

    GL_CHECK_ERRORS
    //enable vertex attribute array for position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,0);

    GL_CHECK_ERRORS
    return 1;

}


