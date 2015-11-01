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
    std::vector<Direction> directions({ 
        Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT 
    });

    auto index = mRng.random(0, 3);
    auto direction = directions[index];

    glm::ivec2 moveDelta;
    switch(direction)
    {
        case Direction::UP: moveDelta = glm::ivec2(0, -1); break;
        case Direction::DOWN: moveDelta = glm::ivec2(0, 1); break;
        case Direction::LEFT: moveDelta = glm::ivec2(-1, 0); break;
        case Direction::RIGHT: moveDelta = glm::ivec2(1, 0); break;
        // LCOV_EXCL_START
        default: ASSERT(false, "This shouldn't happen");
        // LCOV_EXCL_STOP
    };

    auto position = mOwner["position"].get<glm::ivec2>();
    
    return std::make_shared<glm::ivec2>(position + moveDelta);
}
