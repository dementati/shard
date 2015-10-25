#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "../core/Object.hpp"
#include "Need.hpp"

// LCOV_EXCL_START
class Entity : public Object
{
    std::vector<std::unique_ptr<Need>> needs;

public:
    glm::ivec2 position;
    const std::string renderableId;

    Entity(const std::string renderableId);

    Entity(Entity&& entity);

    void addNeed(std::unique_ptr<Need>);

    Need& selectNeed();

    const std::string unitName() const;
};
// LCOV_EXCL_STOP
