#include "drawing.h"


Drawing::Drawing(const Drawing& rhs): vertices(rhs.vertices),
    indices(rhs.indices), points(rhs.points), texture(rhs.texture) {}

Drawing::Drawing(Drawing && rhs): vertices(std::move(rhs.vertices)),
    indices(std::move(rhs.indices)), points(std::move(rhs.points)),
    texture(std::move(rhs.texture)) {}

Drawing& Drawing::operator= (const Drawing& rhs) {
    Drawing tmp(rhs);
    *this = std::move(tmp);
    return *this;
}

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

std::shared_ptr<GLuint> Drawing::getTexture() const
{
    return this->texture;
}

std::vector<glm::mat4> Drawing::getTransforms(float seconds) const
{
    return std::vector<glm::mat4>{glm::mat4(1.0)};
}

std::shared_ptr<Bones> Drawing::getSkeleton() const {
    return nullptr;
}










