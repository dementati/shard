#include "Move.hpp"

Move::Move(JobStack &jobStack, World &world, Entity &owner, glm::ivec2 target)
:
    mWorld(world),
    mOwner(owner),
    mTarget(target),
    mLogger(LoggerFactory::createLogger("Move", Severity::DEBUG)),
    mEntityUtils(std::make_unique<EntityUtils>()),
    mGameObjectUtils(std::make_unique<GameObjectUtils>()),
    mJobStack(jobStack)
{
    ASSERT(owner.hasAttribute("position"), "Owner must have a position");
    ASSERT(owner["position"].isOfType<glm::ivec2>(), "Position must be a glm::ivec2");
    ASSERT(owner["position"].get<glm::ivec2>() != target, "Cannot move to target if owner is already at target");
    ASSERT(owner.hasAttribute("perception"), "Owner must have perception");
    ASSERT(owner["perception"].isOfType<unsigned int>(), "Perception must be an unsigned int");
    ASSERT(mGameObjectUtils->getPerceptionBox(owner).contains(target), "Target must be in perceptive range of the owner");
}

void Move::execute(unsigned int dt)
{
    LOG_DEBUG(mLogger, "Executing.");

    mEntityUtils->updateStepTimer(mOwner, dt);

    if(mEntityUtils->canMove(mOwner))
    {
        LOG_DEBUG(mLogger, "Can move.");

        auto position = mOwner["position"].get<glm::ivec2>();
        auto path = 
            Pathfinding::findPath(
                position, 
                mTarget, 
                [&] (auto p) { return this->isBlocked(p); }, 
                mGameObjectUtils->getPerceptionBox(mOwner));

        if(path.size() > 0)
        {
            ASSERT(path.size() > 1, "Pathfinding returned a path of size 1, which doesn't make sense");
            LOG_DEBUG(mLogger, "Moving to " << glm::to_string(path[path.size() - 2]));
            mEntityUtils->move(mWorld, mOwner, path[path.size() - 2] - position);

            if(path.size() == 2)
            {
                ASSERT(mJobStack.size() > 0, "Supplied job stack must not be empty");
                ASSERT(mJobStack.back().get() == this, "Top of supplied job stack should be this job");
                mJobStack.pop_back();
            }
        }
    } 
}

bool Move::isBlocked(glm::ivec2 position)
{
    LOG_DEBUG(mLogger, "isBlocked(" << glm::to_string(position) << ")");
    return mWorld.isBlocked(position);
}
