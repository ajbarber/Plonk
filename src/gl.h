#ifndef gl_h
#define gl_h

#ifdef HAVE_GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#else
#error no glew.h
#endif

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

#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);

#endif // gl_h
