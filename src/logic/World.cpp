#include "World.hpp"

// LCOV_EXCL_START
void World::add(Entity entity)
{
    entities.push_back(entity);
}

std::vector<Entity>& World::getEntities()
{
    return entities;
}
// LCOV_EXCL_STOP
