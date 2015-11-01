#include "Wander.hpp"

Wander::Wander(World &world, Entity &owner, RNG &rng)
:
    mWorld(world),
    mOwner(owner),
    mRng(rng)
{
}

void Wander::execute(unsigned int dt)
{
    if(canMove(dt))
    {
        auto target = findTarget();
        if(target != nullptr)
        {
            mOwner["position"].set<glm::ivec2>(*target);
        }
    }
}

bool Wander::canMove(unsigned int dt)
{
    unsigned int timeSinceLastStep = mOwner["timeSinceLastStep"].get<unsigned int>() + dt;
    mOwner["timeSinceLastStep"].set<unsigned int>(timeSinceLastStep);
    unsigned int stepLimit = (unsigned int)(1000.0f / mOwner["speed"].get<float>());

    return timeSinceLastStep >= stepLimit;
}

std::shared_ptr<glm::ivec2> Wander::findTarget()
{
    return nullptr;
}
