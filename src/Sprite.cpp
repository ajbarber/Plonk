#include "Sprite.h"


Sprite::Sprite(const unsigned int numberOfTextures) 
{
    textures=new GLuint[numberOfTextures];
    textureIndex = 0;
    currentFrame = 0;
    numberOfFrames = 0;
    animationDelay = 0.25f;
    animationElapsed = 0.0f;
    position.x = 0.0f;
    position.y = 0.0f;
    size.height = 0.0f;
    size.width = 0.0f;
    velocity = 0.0f;
    
    isCollideable = true;
    flipHorizontal = false;
    flipVertical = false;
    isVisible = false;
    isActive = false;
    isSpriteSheet = false;    
}

const bool Sprite::AddTexture(const char* fileName, const bool useTransparency)
{
    
    GLuint texture = SOIL_load_OGL_texture(fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
    if (texture == 0)
    {
        return false;
    }
    
    textures[textureIndex] = texture;
    textureIndex++;
    if (textureIndex == 1 && numberOfFrames > 1) 
    {
        isSpriteSheet=true;
    }
    else 
    {
        isSpriteSheet=false;
    }
    this->useTransparency=useTransparency;
    return true;
}


Sprite::~Sprite() 
{
    delete[] textures;
}



