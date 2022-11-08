#ifndef MainGL_h
#define MainGL_h

#include "gl.h"
#include <SFML/Window.hpp>
#include "world.h"
#include <stdio.h>

class MainGL
{
public:
    MainGL(int argc = 0, char **argv = 0);
    ~MainGL();

    int main(int argx, char **argv);

private:
    static bool checkErrors();
};

#endif // mainGL_h
