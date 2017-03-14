
#include "gl.h"

void initGL()
{  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void drawSolidTriangle()
{  
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.1f, -0.6f);
    glVertex2f(0.7f, -0.6f);
    glVertex2f(0.4f, -0.1f);
    glEnd();
}

void update()
{  
    glClear(GL_COLOR_BUFFER_BIT);
    drawSolidTriangle();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutCreateWindow("Plonk");
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);
    glutDisplayFunc(update);
    initGL();
    glutMainLoop();
    return 0;
}


