#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "Entity.hpp"
#include "GameObject.hpp"

class World
{
    std::vector<std::unique_ptr<Entity>> mEntities = std::vector<std::unique_ptr<Entity>>();
    std::vector<std::unique_ptr<GameObject>> mItems = std::vector<std::unique_ptr<GameObject>>();

public:
    virtual ~World();

    virtual std::vector<std::unique_ptr<Entity>>& getEntities();

    virtual void addEntity(std::unique_ptr<Entity> entity);

    virtual void removeEntity(Entity &entity);

    virtual std::vector<std::unique_ptr<GameObject>>& getItems();

    virtual void addItem(std::unique_ptr<GameObject> item);

    virtual void removeItem(GameObject& item);
};
