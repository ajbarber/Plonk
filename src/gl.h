#ifdef HAVE_GL_GL_H
#include <GL/gl.h>
#elif defined(HAVE_OPENGL_GL_H)
#include <OpenGL/gl.h>
#else
#error no gl.h
#endif

#if defined(HAVE_GL_GLU_H)
#include <GL/glu.h>
#elif defined(HAVE_OPENGL_GLU_H)
#include <OpenGL/glu.h>
#else
#error no glu.h
#endif

#ifdef HAVE_GLUT_GLUT_H
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
