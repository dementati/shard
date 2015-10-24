#pragma once

#include <string>

#include <glm/glm.hpp>

#include "../core/Object.hpp"

// LCOV_EXCL_START
class Entity : public Object
{
    const std::string renderableId;

public:
    Entity(const std::string renderableId);

    const std::string getRenderableId();

    const std::string unitName() const;

    glm::ivec2 position;
};
// LCOV_EXCL_STOP
