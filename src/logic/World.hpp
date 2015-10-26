#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "Entity.hpp"

class World
{
    std::vector<Entity> entities;

public:
    virtual std::vector<Entity>& getEntities();

    virtual void add(Entity entity);
};
