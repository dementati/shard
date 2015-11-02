#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "Entity.hpp"
#include "GameObject.hpp"

class World
{
    std::vector<std::unique_ptr<Entity>> mEntities = std::vector<std::unique_ptr<Entity>>();
    std::vector<std::unique_ptr<GameObject>> mObjects = std::vector<std::unique_ptr<GameObject>>();

public:
    virtual ~World();

    virtual std::vector<std::unique_ptr<Entity>>& getEntities();

    virtual void addEntity(std::unique_ptr<Entity> entity);

    virtual void removeDeadEntities();

    virtual std::vector<std::unique_ptr<GameObject>>& getObjects();

    virtual void addObject(std::unique_ptr<GameObject> object);

    virtual void removeObject(GameObject& object);
};
