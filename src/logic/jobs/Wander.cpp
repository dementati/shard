#include "Wander.hpp"

Wander::Wander(World &world, Entity &owner, RNG &rng)
:
    mWorld(world),
    mOwner(owner),
    mRng(rng),
    mLogger(LoggerFactory::createLogger("Wander", Severity::DEBUG)),
    mEntityUtils(std::make_unique<EntityUtils>())
{
    ASSERT(owner.hasAttribute("position"), "Owner must have a position");
    ASSERT(owner["position"].isOfType<glm::ivec2>(), "Position must be a glm::ivec2");
    ASSERT(owner.hasAttribute("timeSinceLastStep"), "Owner must have timeSinceLastStep");
    ASSERT(owner["timeSinceLastStep"].isOfType<unsigned int>(), "timeSinceLastStep must be an unsigned int");
    ASSERT(owner.hasAttribute("speed"), "Owner must have speed");
    ASSERT(owner["speed"].isOfType<float>(), "speed must be a float");
}

void Wander::execute(unsigned int dt)
{
    LOG_DEBUG(mLogger, "Executing.");

    mEntityUtils->updateStepTimer(mOwner, dt);

    if(mEntityUtils->canMove(mOwner))
    {
        LOG_DEBUG(mLogger, "Can move.");

        auto direction = findDirection();
        if(direction != nullptr)
        {
            LOG_DEBUG(mLogger, "Moving to " << glm::to_string(*direction));
            mEntityUtils->move(mWorld, mOwner, *direction);
        } 
        else
        {
            // TODO: Test this branch when collision detection is in place
            // LCOV_EXCL_START
            LOG_DEBUG(mLogger, "No viable direction found.");
            // LCOV_EXCL_STOP
        }
    }
}

std::shared_ptr<glm::ivec2> Wander::findDirection()
{
    std::vector<Direction> directions({ 
        Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT 
    });

    auto index = mRng.random(0, 3);
    auto direction = directions[index];

    glm::ivec2 moveDelta;
    switch(direction)
    {
        case Direction::UP: return std::make_shared<glm::ivec2>(0, -1);
        case Direction::DOWN: return std::make_shared<glm::ivec2>(0, 1); 
        case Direction::LEFT: return std::make_shared<glm::ivec2>(-1, 0); 
        case Direction::RIGHT: return std::make_shared<glm::ivec2>(1, 0); 
        // LCOV_EXCL_START
        default: ASSERT(false, "This shouldn't happen");
        // LCOV_EXCL_STOP
    };
}
