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
    isVisible = true;
    isActive = false;
    isSpriteSheet = false;    
}

const bool Sprite::addTexture(const char* fileName, const bool useTransparency)
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

void Sprite::render() {
	if (isVisible) 
	{
		if (useTransparency) 
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			
		}
		
		glBindTexture(GL_TEXTURE_2D, getCurrentFrame());
		
		glBegin(GL_QUADS);
		
		GLfloat x = position.x;
		GLfloat y = position.y;
		
		GLfloat w = size.width;
		GLfloat h = size.height;
		
		GLfloat texWidth = (GLfloat)textureIndex / (GLfloat)numberOfFrames;
		GLfloat texHeight = 1.0f;
		GLfloat u = 0.0f;
		GLfloat v = 0.0f;
		if (textureIndex < numberOfFrames)
		{
			u = (GLfloat)currentFrame * texWidth;	
		
		}
		glTexCoord2f(u,v); glVertex2f(x,y);
		glTexCoord2f(u + texWidth,v); glVertex2f(x + w,y);
		glTexCoord2f(u + texWidth,v + texHeight); glVertex2f(x + w,y + h);
		glTexCoord2f(u,v + texHeight); glVertex2f(x,y  + h);

		glEnd();
		
		if (useTransparency) 
		{
			glDisable(GL_BLEND);
		}
		
		
	}
}


Sprite::~Sprite() 
{
    delete[] textures;
}



