#include "PlayerControl.hpp"

PlayerControl::PlayerControl(InputSystem &input, World &world, Entity &owner)
:
    PlayerControl(input, world, owner, std::make_unique<EntityUtils>())
{
    ASSERT(world.hasAttribute("running"), "World must have running flag");
    ASSERT(world["running"].isOfType<bool>(), "Running flag must be a bool");
    ASSERT(world.hasAttribute("cameraPosition"), "World must have camera position");
    ASSERT(world["cameraPosition"].isOfType<glm::ivec2>(), "Camera position must be a glm::ivec2");

    ASSERT(owner.hasAttribute("position"), "Owner must have a position");
    ASSERT(owner["position"].isOfType<glm::ivec2>(), "Owner must be a glm::ivec2");

    synchronizeCamera();
}

PlayerControl::PlayerControl(InputSystem &input, World &world, Entity &owner, std::unique_ptr<EntityUtils> entityUtils)
:
    mInput(input),
    mWorld(world),
    mOwner(owner),
    mEntityUtils(std::move(entityUtils)),
    mLogger(LoggerFactory::createLogger("PlayerControl", Severity::DEBUG))
{
    ASSERT(world.hasAttribute("running"), "World must have running flag");
    ASSERT(world["running"].isOfType<bool>(), "Running flag must be a bool");
    ASSERT(world.hasAttribute("cameraPosition"), "World must have camera position");
    ASSERT(world["cameraPosition"].isOfType<glm::ivec2>(), "Camera position must be a glm::ivec2");

    ASSERT(owner.hasAttribute("position"), "Owner must have a position");
    ASSERT(owner["position"].isOfType<glm::ivec2>(), "Owner must be a glm::ivec2");

    synchronizeCamera();
}

// LCOV_EXCL_START
void PlayerControl::execute(unsigned int dt)
{
    LOG_DEBUG(mLogger, "Updating step timer.");
    mEntityUtils->updateStepTimer(mOwner, dt);

    if(mEntityUtils->canMove(mOwner))
    {
        LOG_DEBUG(mLogger, "Can move.");
        if(mInput.isPressed(Key::Up))
        {
            mEntityUtils->move(mWorld, mOwner, glm::ivec2(0, -1));
            synchronizeCamera();
        }
        else if(mInput.isPressed(Key::Down))
        {
            mEntityUtils->move(mWorld, mOwner, glm::ivec2(0, 1));
            synchronizeCamera();
        }
        else if(mInput.isPressed(Key::Left))
        {
            mEntityUtils->move(mWorld, mOwner, glm::ivec2(-1, 0));
            synchronizeCamera();
        }
        else if(mInput.isPressed(Key::Right))
        {
            mEntityUtils->move(mWorld, mOwner, glm::ivec2(1, 0));
            synchronizeCamera();
        }
        else if(mInput.isPressed(Key::Use))
        {
            LOG_DEBUG(mLogger, "Use key pressed.");
            LOG_DEBUG(mLogger, "Finding water.");
            GameObject *water = mEntityUtils->getClosestObjectWithAttributeInRange(mWorld, mOwner, "thirstReduction", 1);

            if(water != nullptr)
            {
                LOG_DEBUG(mLogger, "Water found, consuming.");
                mEntityUtils->consumeWater(mWorld, mOwner, *water);
            }
        }
        else if(mInput.isPressed(Key::DrinkBlood))
        {
            LOG_DEBUG(mLogger, "Drink blood key pressed.");
            LOG_DEBUG(mLogger, "Finding blood.");
            GameObject *blood = mEntityUtils->getClosestObjectWithAttributeInRange(mWorld, mOwner, "blood", 1);

            if(blood != nullptr)
            {
                LOG_DEBUG(mLogger, "Blood found, consuming.");
                mEntityUtils->consumeWater(mWorld, mOwner, *blood);
            }
        }
        else if(mInput.isPressed(Key::Quit))
        {
            mWorld["running"].set<bool>(false);
        }
    }
}
// LCOV_EXCL_STOP

void PlayerControl::synchronizeCamera()
{
    mWorld["cameraPosition"].set<glm::ivec2>(mOwner["position"].get<glm::ivec2>() - glm::ivec2(32, 18));
}
