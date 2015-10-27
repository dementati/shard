#include "World.hpp"

// LCOV_EXCL_START
World::~World()
{
}
// LCOV_EXCL_STOP

std::vector<std::unique_ptr<Entity>>& World::getEntities()
{
    return entities;
}

void World::add(std::unique_ptr<Entity> entity)
{
    entities.push_back(std::move(entity));
}
