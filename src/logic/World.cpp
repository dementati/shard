#include "World.hpp"

// LCOV_EXCL_START
void World::add(Entity entity)
{
    entities.push_back(std::move(entity));
}
// LCOV_EXCL_STOP
