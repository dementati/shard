#pragma once

#include <glm/glm.hpp>

#include "../Entity.hpp"

class Entity;

class EntityUtils
{
public:
    virtual ~EntityUtils();

    virtual void updateStepTimer(Entity &entity, unsigned int dt);

    virtual bool canMove(Entity &entity);

    virtual void move(Entity &entity, glm::ivec2 deltaPosition);
};
