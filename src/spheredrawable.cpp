#include "spheredrawable.h"

SphereDrawable::SphereDrawable(const Drawing& drawing): GLDrawable(drawing) {

}

int SphereDrawable::bind()
{

    GLuint sphereVerticesVBO;
    GLuint sphereIndicesVBO;

    std::vector<Vertex> vertices = drawing.getVertices();
    std::vector<GLushort> indices = drawing.getIndices();

    //setup sphere vao and vbo stuff
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &sphereVerticesVBO);
    glGenBuffers(1, &sphereIndicesVBO);
    glBindVertexArray(vaoID);

        glBindBuffer (GL_ARRAY_BUFFER, sphereVerticesVBO);
        //pass vertices to the buffer object
        glBufferData (GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        GL_CHECK_ERRORS
        //enable vertex attribute array for position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(Vertex),0);
        GL_CHECK_ERRORS
        //enable vertex attribute array for normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, normal)));
        GL_CHECK_ERRORS
        //pass sphere indices to element array buffer
        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, sphereIndicesVBO);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLushort), &indices[0], GL_STATIC_DRAW);

    //store the total number of sphere triangles
    numTriangles = indices.size();

    return 0;

}

