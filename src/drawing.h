#ifndef DRAWING_H
#define DRAWING_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "structs.h"
#include "gl.h"

class Drawing
{

public:

    virtual ~Drawing();
    std::vector<Vertex> getVertices() const;
    std::vector<GLushort> getIndices() const;
    std::vector<glm::vec3> getPoints() const;

protected:

    std::vector<Vertex> vertices;
    std::vector<GLushort> indices;
    std::vector<glm::vec3> points;

    inline void push_indices(int sectors, int r, int s, std::vector<GLushort>& indices) {
        int curRow = r * sectors;
        int nextRow = (r+1) * sectors;

        indices.push_back(curRow + s);
        indices.push_back(nextRow + s);
        indices.push_back(nextRow + (s+1));

        indices.push_back(curRow + s);
        indices.push_back(nextRow + (s+1));
        indices.push_back(curRow + (s+1));
    }

private:


};

#endif // DRAWING_H
