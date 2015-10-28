#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "Entity.hpp"

class World
{
    std::vector<std::unique_ptr<Entity>> mEntities = std::vector<std::unique_ptr<Entity>>();

public:
    virtual ~World();

    virtual std::vector<std::unique_ptr<Entity>>& getEntities();

    virtual void add(std::unique_ptr<Entity> entity);
};
