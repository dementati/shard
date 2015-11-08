#pragma once

#include <glm/glm.hpp>

#include "../../utility/math/geometry/Box.hpp"
#include "../../utility/math/Math.hpp"
#include "../Entity.hpp"
#include "../World.hpp"

class Entity;

class EntityUtils
{
public:
    virtual ~EntityUtils();

    virtual void updateStepTimer(Entity &entity, unsigned int dt);

    virtual bool canMove(Entity &entity);

    virtual void move(World &world, Entity &entity, glm::ivec2 deltaPosition);

    virtual GameObject* getClosestObjectWithAttributeInRange(World &world, Entity &entity, std::string attribute, unsigned int range);

    virtual void consumeWater(World &world, Entity &entity, GameObject &water);
};
