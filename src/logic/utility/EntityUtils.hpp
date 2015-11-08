#pragma once

#include <glm/glm.hpp>

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
};
