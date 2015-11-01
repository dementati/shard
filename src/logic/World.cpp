#include "World.hpp"

// LCOV_EXCL_START
World::~World()
{
}
// LCOV_EXCL_STOP

std::vector<std::unique_ptr<Entity>>& World::getEntities()
{
    return mEntities;
}

void World::addEntity(std::unique_ptr<Entity> entity)
{
    mEntities.push_back(std::move(entity));
}

void World::removeEntity(Entity &entity)
{
    mEntities.erase(
        std::remove_if(mEntities.begin(), mEntities.end(), 
            // LCOV_EXCL_START
            [&] (auto &entityPtr) { return entityPtr.get() == &entity; }
            // LCOV_EXCL_STOP
        ), 
        mEntities.end());
}

std::vector<std::unique_ptr<GameObject>>& World::getObjects()
{
    return mObjects;
}

void World::addObject(std::unique_ptr<GameObject> object)
{
    mObjects.push_back(std::move(object));
}

void World::removeObject(GameObject &object)
{
    mObjects.erase(
        std::remove_if(mObjects.begin(), mObjects.end(),
            // LCOV_EXCL_START
            [&] (auto &objectPtr) { return objectPtr.get() == &object; }
            // LCOV_EXCL_STOP
        ), 
        mObjects.end());
}
