#include "World.hpp"

std::vector<Entity>& World::getEntities()
{
    return entities;
}

void World::add(Entity entity)
{
    entities.push_back(entity);
}
