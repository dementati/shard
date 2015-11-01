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
            [&] (auto &entityPtr) {
                return entityPtr.get() == &entity;
            }
        ), 
        mEntities.end());
}

std::vector<std::unique_ptr<GameObject>>& World::getItems()
{
    return mItems;
}

void World::addItem(std::unique_ptr<GameObject> item)
{
    mItems.push_back(std::move(item));
}

void World::removeItem(GameObject &item)
{
    mItems.erase(
        std::remove_if(mItems.begin(), mItems.end(), 
            [&] (auto &itemPtr) {
                return itemPtr.get() == &item;
            }
        ), 
        mItems.end());
}
