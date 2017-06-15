#include "herodrawable.h"


HeroBodyPartDrawable::HeroBodyPartDrawable(const Drawing& drawing): GLDrawable(drawing)
{

}

int HeroBodyPartDrawable::bindDrawing()
{
    GLuint verticesVBO;
    GLuint indicesVBO;

    std::vector<Vertex> vertices = drawing.getVertices();
    std::vector<GLushort> indices = drawing.getIndices();

    //setup cube vao and vbo stuff
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &verticesVBO);
    glGenBuffers(1, &indicesVBO);
    glBindVertexArray(vaoID);

    glBindBuffer (GL_ARRAY_BUFFER, verticesVBO);
    //pass vertices to the buffer object
    glBufferData (GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    GL_CHECK_ERRORS
    //enable vertex attribute array for position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(Vertex),0);
    GL_CHECK_ERRORS
    //enable vertex attribute array for normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, normal)));
    GL_CHECK_ERRORS
    //enable vertex attribute array for texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, tex)));
    GL_CHECK_ERRORS
    //pass cube indices to element array buffer
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLushort), &indices[0], GL_STATIC_DRAW);


    numTriangles = indices.size();
    fprintf(stderr, "Handle : %d: ", *drawing.getTexture() );
    checkErrors();

    GL_CHECK_ERRORS
    return 0;

}

int HeroBodyPartDrawable::bindTexture()
{
    //bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *drawing.getTexture());

}


bool HeroBodyPartDrawable::checkErrors()
{

    bool retVal = false;
    GLenum	gl_error;

    //-- Check for GL errors
    gl_error = glGetError( );
    if( gl_error != GL_NO_ERROR )
    {
        fprintf(stderr, "ERROR!!! OpenGL error: %s\n", gluErrorString(gl_error) );
        retVal = true;
    }

    return retVal;
}




