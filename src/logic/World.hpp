#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <utility>

#include "../utility/VectorHash.hpp"
#include "Entity.hpp"
#include "GameObject.hpp"

class World : public GameObject
{
    GameObject mState;
    std::vector<std::unique_ptr<Entity>> mEntities = std::vector<std::unique_ptr<Entity>>();
    std::vector<std::unique_ptr<GameObject>> mObjects = std::vector<std::unique_ptr<GameObject>>();

public:
    World();

    virtual ~World();

    virtual std::vector<std::unique_ptr<Entity>>& getEntities();

    virtual void addEntity(std::unique_ptr<Entity> entity);

    virtual void removeDeadEntities();

    virtual std::vector<std::unique_ptr<GameObject>>& getObjects();

    virtual void addObject(std::unique_ptr<GameObject> object);

    virtual void removeObject(GameObject& object);

    virtual void setBlockedMapIfSolid(GameObject &object, bool blocked);

    virtual bool isBlocked(glm::ivec2 position);
};
