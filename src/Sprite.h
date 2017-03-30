#ifndef SPRITE_H
#define SPRITE_H

#include "gl.h"
#include "Image.h"
#include "../lib/soil/src/SOIL.h"
#include <stdio.h>



class Sprite {
public: 
    struct Point {
        GLfloat x;
        GLfloat y;
    };
    
    struct Size {
        GLfloat width;
        GLfloat height;
    };
    
    struct Rect {
        GLfloat top;
        GLfloat bottom;
        GLfloat left;
        GLfloat right;            
    };
    
protected : 
    GLuint* textures;
    unsigned int textureIndex;
    unsigned int currentFrame;  
    unsigned int numberOfFrames;
    GLfloat animationDelay;
    GLfloat animationElapsed;
    
    Point position;
    Size size;
    GLfloat velocity;
    
    bool isCollideable;
    bool flipHorizontal;
    bool flipVertical;
    bool isVisible;
    bool isActive;
    bool useTransparency;
    bool isSpriteSheet;
    
public:
    Sprite(const unsigned int numberOfTextures);
    ~Sprite();
    
    void update(const float deltaTime);
    void render();
    
    const bool addTexture(const char* fileName, const bool useTransparency=true);
    const GLuint getCurrentFrame() { 
        if (isSpriteSheet) 
        {
            return textures[0];
        }
        else 
        {
            return textures[currentFrame];
        }            
    }
    
    void setPosition(const GLfloat x,const GLfloat y) {
        position.x=x;
        position.y=y; 
    }
    
    void setPosition(const Point pos) {
        position = pos;
    }
    
    const Point getPosition () {
        return position;
    }
    
    const Size getSize() const {
        return size;
    }
    
    void setFrameSize(const GLfloat width, const GLfloat height) {
        size.width = width;
        size.height = height;
    }
    
    void setVelocity(const GLfloat velocity) {
        this->velocity=velocity;        
    }
    
    void setNumberOfFrames(const unsigned int nframes) {
        numberOfFrames=nframes;
    }
    
    const bool getIsCollideable() const { return isCollideable; }
    
    void getIsCollideable(const bool value) {
        this->isCollideable=value;
    }
    
    void setFlipHorizontal(bool value) {
        this->flipHorizontal=value;
    }
    
    void setIsActive(const bool value) {
        this->isActive = value; 
    }
    
    const bool getIsActive() const {
        return isActive; 
    }
    
    void setIsVisible(const bool value) { isVisible = value; }
    
    const bool getIsVisible() const { return isVisible; }
    
    void setUseTransparency(const bool value) { useTransparency = value; }
        
};

#endif