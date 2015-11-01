#include "Move.hpp"

Move::Move(World &world, Entity &owner, glm::ivec2 target)
:
    mWorld(world),
    mOwner(owner),
    mTarget(target),
    mLogger(LoggerFactory::createLogger("Move", Severity::DEBUG))
{
    ASSERT(owner.hasAttribute("position"), "Owner must have a position");
    ASSERT(owner["position"].isOfType<glm::ivec2>(), "Position must be a glm::ivec2");
    ASSERT(owner["position"].get<glm::ivec2>() != target, "Cannot move to target if owner is already at target");
    ASSERT(owner.hasAttribute("perception"), "Owner must have perception");
    ASSERT(owner["perception"].isOfType<unsigned int>(), "Perception must be an unsigned int");
    ASSERT(owner.hasAttribute("timeSinceLastStep"), "Owner must have timeSinceLastStep");
    ASSERT(owner["timeSinceLastStep"].isOfType<unsigned int>(), "timeSinceLastStep must be an unsigned int");
    ASSERT(owner.hasAttribute("speed"), "Owner must have speed");
    ASSERT(owner["speed"].isOfType<float>(), "speed must be a float");
    ASSERT(GameObjectUtils::getPerceptionBox(owner).contains(target), "Target must be in perceptive range of the owner");
}

void Move::execute(unsigned int dt)
{
    mLogger->debug("Executing.");

    auto stepCount = getStepCount(dt);
    if(stepCount > 0)
    {
        mLogger->debug(std::string("Max nr of steps is ") + glm::to_string(stepCount));

        auto path = 
            Pathfinding::findPath(
                mOwner["position"].get<glm::ivec2>(), 
                mTarget, 
                [&] (auto p) { return this->isBlocked(p); }, 
                GameObjectUtils::getPerceptionBox(mOwner));

        auto pathIndex = path.size() - 1 >= stepCount ? path.size() - 1 - stepCount : 0;
        mOwner["position"].set<glm::ivec2>(path[pathIndex]);
        mOwner["timeSinceLastStep"].set<unsigned int>(0);

        mLogger->debug(std::string("Moving to ") + glm::to_string(path[pathIndex]));
    } 
}

bool Move::isBlocked(glm::ivec2 position)
{
    ASSERT(position == position, "");

    return false;
}

unsigned int Move::getStepCount(unsigned int dt)
{
    unsigned int timeSinceLastStep = mOwner["timeSinceLastStep"].get<unsigned int>() + dt;
    mOwner["timeSinceLastStep"].set<unsigned int>(timeSinceLastStep);
    unsigned int timePerStep = (unsigned int)(1000.0f / mOwner["speed"].get<float>());

    return (unsigned int)(timeSinceLastStep / timePerStep);
}
