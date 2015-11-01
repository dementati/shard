#include "Move.hpp"

Move::Move(World &world, Entity &owner, glm::ivec2 target)
:
    mWorld(world),
    mOwner(owner),
    mTarget(target)
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
    ASSERT(getPerceptionBox().contains(target), "Target must be in perceptive range of the owner");
}

void Move::execute(unsigned int dt)
{
    auto stepCount = getStepCount(dt);
    if(stepCount > 0)
    {
        auto path = 
            Pathfinding::findPath(
                mOwner["position"].get<glm::ivec2>(), 
                mTarget, 
                [&] (auto p) { return this->isBlocked(p); }, 
                getPerceptionBox());

        auto pathIndex = path.size() - 1 >= stepCount ? path.size() - 1 - stepCount : 0;
        mOwner["position"].set<glm::ivec2>(path[pathIndex]);
        mOwner["timeSinceLastStep"].set<unsigned int>(0);
    }
}

bool Move::isBlocked(glm::ivec2 position)
{
    ASSERT(position == position, "");

    return false;
}

Box Move::getPerceptionBox()
{
    int perception = mOwner["perception"].get<unsigned int>();
    ASSERT(perception > 0, "Cannot navigate with 0 perception");

    glm::ivec2 position = mOwner["position"].get<glm::ivec2>();

    return Box(position - perception*glm::ivec2(1, 1), (2*perception + 1)*glm::ivec2(1, 1));
}

unsigned int Move::getStepCount(unsigned int dt)
{
    unsigned int timeSinceLastStep = mOwner["timeSinceLastStep"].get<unsigned int>() + dt;
    mOwner["timeSinceLastStep"].set<unsigned int>(timeSinceLastStep);
    unsigned int timePerStep = (unsigned int)(1000.0f / mOwner["speed"].get<float>());

    return (unsigned int)(timeSinceLastStep / timePerStep);
}
