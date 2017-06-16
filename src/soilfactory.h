#ifndef SOILFACTOR_H
#define SOILFACTOR_H
#include "gl.h"
#include <memory>

class SoilFactory
{
public:
    static std::shared_ptr<GLuint> load(std::string fileName);


private:     


};

#endif // SOILFACTOR_H
