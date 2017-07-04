#ifndef DRAWING_H
#define DRAWING_H

#include <vector>
#include <memory>
#include "structs.h"
#include "gl.h"

class Drawing
{

public:

    Drawing() {}
    Drawing(Drawing &&);
    Drawing(const Drawing& rhs);
    Drawing& operator= (const Drawing& rhs);
    virtual ~Drawing() {}
    virtual std::vector<Vertex> getVertices() const;
    virtual std::vector<GLushort> getIndices() const;
    virtual std::vector<glm::vec3> getPoints() const;
    virtual std::shared_ptr<GLuint> getTexture() const;

protected:

    std::vector<Vertex> vertices;
    std::vector<GLushort> indices;
    std::vector<glm::vec3> points;
    std::shared_ptr<GLuint> texture;

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
