#include "EntityUtils.hpp"

EntityUtils::~EntityUtils()
{
}

void EntityUtils::updateStepTimer(Entity &entity, unsigned int dt)
{
    ASSERT(entity.hasAttribute("timeSinceLastStep"), "Entity must have timeSinceLastStep");
    ASSERT(entity["timeSinceLastStep"].isOfType<unsigned int>(), "timeSinceLastStep must be an unsigned int");

    unsigned int timeSinceLastStep = entity["timeSinceLastStep"].get<unsigned int>() + dt;
    entity["timeSinceLastStep"].set<unsigned int>(timeSinceLastStep);
}

bool EntityUtils::canMove(Entity &entity)
{
    ASSERT(entity.hasAttribute("timeSinceLastStep"), "Entity must have timeSinceLastStep");
    ASSERT(entity["timeSinceLastStep"].isOfType<unsigned int>(), "timeSinceLastStep must be an unsigned int");
    ASSERT(entity.hasAttribute("speed"), "Entity must have speed");
    ASSERT(entity["speed"].isOfType<float>(), "speed must be a float");

    unsigned int timeSinceLastStep = entity["timeSinceLastStep"].get<unsigned int>();
    unsigned int stepLimit = (unsigned int)(1000.0f / entity["speed"].get<float>());
    return timeSinceLastStep >= stepLimit;
}

void EntityUtils::move(Entity &entity, glm::ivec2 deltaPosition)
{
    ASSERT(entity.hasAttribute("position"), "Entity must have a position");
    ASSERT(entity["position"].isOfType<glm::ivec2>(), "Position must be a glm::ivec2");
    ASSERT(entity.hasAttribute("timeSinceLastStep"), "Entity must have timeSinceLastStep");
    ASSERT(entity["timeSinceLastStep"].isOfType<unsigned int>(), "timeSinceLastStep must be an unsigned int");
    ASSERT(deltaPosition != glm::ivec2(0, 0), "deltaPosition cannot be (0, 0)");

    entity["timeSinceLastStep"].set<unsigned int>(0);
    auto position = entity["position"].get<glm::ivec2>() + deltaPosition;
    entity["position"].set<glm::ivec2>(position);
}
