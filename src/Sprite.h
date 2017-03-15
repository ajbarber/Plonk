#ifndef SPRITE_H
#define SPRITE_H

#include "gl.h"
#include "../lib/soil/src/SOIL.h"



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
    
    void Update(const float deltaTime);
    void Render();
    
    const bool AddTexture(const char* fileName, const bool useTransparency=true);
    const GLuint GetCurrentFrame() { 
        if (isSpriteSheet) 
        {
            return textures[0];
        }
        else 
        {
            return textures[currentFrame];
        }            
    }
    
    void SetPosition(const GLfloat x,const GLfloat y) {
        this->position.x=x;
        this->position.y=y; 
    }
    
    void SetPosition(const Point pos) {
        position = pos;
    }
    
    const Point GetPosition () {
        return position;
    }
    
    const Size GetSize() const {
        return size;
    }
    
    void SetFrameSize(const GLfloat width, const GLfloat height) {
        size.width = width;
        size.height = height;
    }
    
    void SetVelocity(const GLfloat velocity) {
        this->velocity=velocity;        
    }
    
    void SetNumberOfFrames(const unsigned int nframes) {
        numberOfFrames=nframes;
    }
    
    const bool IsCollideable() const { return isCollideable; }
    
    void IsCollideable(const bool value) {
        this->isCollideable=value;
    }
    
    void FlipHorizontal(bool value) {
        this->flipHorizontal=value;
    }
    
    void IsActive(const bool value) {
        this->isActive = value; 
    }
    
    const bool IsActive() const {
        return isActive; 
    }
    
    void IsVisible(const bool value) { isVisible = value; }
    
    const bool IsVisible() const { return isVisible; }
    
    void UseTransparency(const bool value) { useTransparency = value; }
        
};

#endif