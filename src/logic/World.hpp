#pragma once

#include <vector>

#include "Entity.hpp"

class World
{
    std::vector<Entity> entities;

public:
    void add(Entity entity);

    std::vector<Entity>& getEntities();
};
