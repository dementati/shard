#pragma once

#include <utility>
#include <vector>

#include "Entity.hpp"

class World
{

public:
    std::vector<Entity> entities;

    void add(Entity entity);
};
