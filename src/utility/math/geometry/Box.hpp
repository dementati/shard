#pragma once

#include <glm/glm.hpp>

#include "../../Assert.hpp"

class Box
{
    glm::ivec2 mPosition;
    glm::uvec2 mDimensions;

public:
    Box(glm::ivec2 position, glm::uvec2 dimensions);

    bool contains(glm::ivec2 position);

    unsigned int getVolume() const;

    glm::ivec2 getPosition() const;

    glm::uvec2 getDimensions() const;
};
