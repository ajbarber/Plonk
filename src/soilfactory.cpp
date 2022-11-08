#include "soilfactory.h"
#include <string>
#include "../lib/soil/src/SOIL.h"
#include <assert.h>

std::shared_ptr<GLuint> SoilFactory::load(std::string fileName)
{
    GLuint* textureHdl = new GLuint();

    int width, height, channels;

    assert(!fileName.empty());
    unsigned char* image = SOIL_load_image(fileName.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);

    assert(image != 0);

    glGenTextures(1, textureHdl);
    glBindTexture(GL_TEXTURE_2D, *textureHdl);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (image != 0)
        SOIL_free_image_data(image);

    std::shared_ptr<GLuint> res = nullptr;

    if (image == 0)
    {
        fprintf(stderr, "SOIL error loading file: %s '%s'\n", fileName.c_str(), SOIL_last_result() );
    }
    else
    {
        res = std::shared_ptr<GLuint>(textureHdl);
    }
    return res;
}
