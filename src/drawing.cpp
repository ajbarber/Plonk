#include "drawing.h"

Drawing::~Drawing() {}

std::vector<Vertex> Drawing::getVertices() const
{
    return this->vertices;
}

std::vector<GLushort> Drawing::getIndices() const
{
    return this->indices;
}

std::vector<glm::vec3> Drawing::getPoints() const
{
    return this->points;
}






