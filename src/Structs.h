#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include "gl.h"

#define X_POS 0
#define Y_POS 1
#define Z_POS 2

#define U_POS 0
#define V_POS 1

#define R_POS 0
#define G_POS 1
#define B_POS 2
#define A_POS 3

#define WORLD_WIDTH 4048
#define WORLD_HEIGHT 4048

#define SCREEN_WIDTH 800.f
#define SCREEN_HEIGHT 600.f

struct Vertex
{
    GLfloat location[3];
    GLfloat tex[2];
    GLfloat normal[3];
    GLfloat color[4];
    GLubyte padding[16];        // Pads the struct out to 64 bytes for performance increase
};


struct Plane
{
    float a;
    float b;
    float c;
    float d;
};


#endif